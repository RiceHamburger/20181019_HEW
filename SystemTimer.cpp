//=====================================================================//
//		システムタイマー [systemTimer.cpp]                             //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/06/15            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "SystemTimer.h"

//=====================================================================//
//                                                                     //
//							グローバル変数宣言	                       //
//                                                                     //
//=====================================================================//
static bool g_bTimerStopped = true; // ストップフラグ
static LONGLONG g_TicksPerSec = 0;  // １秒間の計測時間
static LONGLONG g_StopTime;         // ストップした時間
static LONGLONG g_LastElapsedTime;  // 最後に記録した更新時間
static LONGLONG g_BaseTime;         // 基本時間

/* --------------------------------
停止していれば停止時間、そうでなければ現在の時間の取得
-------------------------------- */
static LARGE_INTEGER GetAdjustedCurrentTime(void);


//=====================================================================//
//                                                                     //
//						システムタイマーの初期化					   //
//                                                                     //
//=====================================================================//
void SystemTimerInitialize(void)
{
	/* --------------------------------
	変数初期化
	-------------------------------- */
    g_bTimerStopped = true;
    g_TicksPerSec = 0;
    g_StopTime = 0;
    g_LastElapsedTime = 0;
    g_BaseTime = 0;

	/* --------------------------------
	高分解能パフォーマンスカウンタ周波数の取得
	-------------------------------- */
    LARGE_INTEGER ticksPerSec = { 0 };
    QueryPerformanceFrequency(&ticksPerSec);
    g_TicksPerSec = ticksPerSec.QuadPart;
}
//=====================================================================//
//                                                                     //
//						システムタイマーのリセット					   //
//                                                                     //
//=====================================================================//
void SystemTimerReset(void)
{
	/* --------------------------------
	タイマーリセット
	-------------------------------- */
    LARGE_INTEGER time = GetAdjustedCurrentTime();

    g_BaseTime = g_LastElapsedTime = time.QuadPart;
    g_StopTime = 0;
    g_bTimerStopped = false;
}
//=====================================================================//
//                                                                     //
//						システムタイマーのスタート					   //
//                                                                     //
//=====================================================================//
void SystemTimerStart(void)
{
	/* --------------------------------
	現在の時間を取得
	-------------------------------- */
    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);
	/* --------------------------------
	今まで計測がストップしていたら
	-------------------------------- */
    if( g_bTimerStopped ) 
	{
		/* --------------------------------
		止まっていた時間を差し引いて基本時間を更新
		-------------------------------- */
        g_BaseTime += time.QuadPart - g_StopTime;
    }
	/* --------------------------------
	リセット設定
	-------------------------------- */
    g_StopTime = 0;
    g_LastElapsedTime = time.QuadPart;
    g_bTimerStopped = false;
}
//=====================================================================//
//                                                                     //
//						システムタイマーのストップ					   //
//                                                                     //
//=====================================================================//
void SystemTimerStop(void)
{
	/* --------------------------------
	タイマーが停止したら
	-------------------------------- */
    if( g_bTimerStopped ) return;

	/* --------------------------------
	リセット設定
	-------------------------------- */
    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);
	/* --------------------------------
	停止時間を記録
	-------------------------------- */
    g_LastElapsedTime = g_StopTime = time.QuadPart;
    g_bTimerStopped = true;
}

//=====================================================================//
//                                                                     //
//						システムタイマーの0.1秒進					   //
//                                                                     //
//=====================================================================//
void SystemTimerAdvance(void)
{	
	/* --------------------------------
	システムタイマーを0.1秒進める
	-------------------------------- */
    g_StopTime += g_TicksPerSec / 10;
}
//=====================================================================//
//                                                                     //
//						ゲットシステムタイマー						   //
//                                                                     //
//=====================================================================//
double SystemTimerGetTime(void)
{
	/* --------------------------------
	ゲット時間
	-------------------------------- */
    LARGE_INTEGER time = GetAdjustedCurrentTime();
	/* --------------------------------
	計測時間をリターン
	-------------------------------- */
    return (double)(time.QuadPart - g_BaseTime) / (double)g_TicksPerSec;
}
//=====================================================================//
//                                                                     //
//						ゲットシステム現在時間						   //
//                                                                     //
//=====================================================================//
double SystemTimerGetAbsoluteTime(void)
{
	/* --------------------------------
	タイマーリセット
	-------------------------------- */
    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);
	/* --------------------------------
	リターンシステム現在時間
	-------------------------------- */
    return time.QuadPart / (double)g_TicksPerSec;
}
//=====================================================================//
//                                                                     //
//						ゲットシステム経過時間						   //
//                                                                     //
//=====================================================================//
float SystemTimerGetElapsedTime(void)
{
	/* --------------------------------
	タイマーリセット 
	計算
	-------------------------------- */
    LARGE_INTEGER time = GetAdjustedCurrentTime();

    double elapsed_time = (float)((double)(time.QuadPart - g_LastElapsedTime) / (double)g_TicksPerSec);
    g_LastElapsedTime = time.QuadPart;

    // タイマーが正確であることを保証するために、更新時間を０にクランプする。
    // elapsed_timeは、プロセッサが節電モードに入るか、何らかの形で別のプロセッサにシャッフルされると、この範囲外になる可能性がある。
    // よって、メインスレッドはSetThreadAffinityMaskを呼び出して、別のプロセッサにシャッフルされないようにする必要がある。
    // 他のワーカースレッドはSetThreadAffinityMaskを呼び出すべきではなく、メインスレッドから収集されたタイマーデータの共有コピーを使用すること。
    if( elapsed_time < 0.0f ) {
        elapsed_time = 0.0f;
    }
	/* --------------------------------
	リターン経過時間
	-------------------------------- */
    return (float)elapsed_time;
}

//=====================================================================//
//                                                                     //
//					システムタイマー状態チェック					   //
//                                                                     //
//=====================================================================//
bool SystemTimerIsStoped(void)
{
	/* --------------------------------
	システムタイマーが止まっているか？
	-------------------------------- */
    return g_bTimerStopped;
}
//=====================================================================//
//                                                                     //
//						プロセッサの制限関数						   //
//                                                                     //
//=====================================================================//
void LimitThreadAffinityToCurrentProc(void)
{
	/* --------------------------------
	現在のスレッドを1つのプロセッサ（現在のスレッド）に制限
	-------------------------------- */
    HANDLE hCurrentProcess = GetCurrentProcess();

    // Get the processor affinity mask for this process
    DWORD_PTR dwProcessAffinityMask = 0;
    DWORD_PTR dwSystemAffinityMask = 0;

    if( GetProcessAffinityMask(hCurrentProcess, &dwProcessAffinityMask, &dwSystemAffinityMask) != 0 && dwProcessAffinityMask ) {
        // Find the lowest processor that our process is allows to run against
        DWORD_PTR dwAffinityMask = (dwProcessAffinityMask & ((~dwProcessAffinityMask) + 1));

        // Set this as the processor that our thread must always run against
        // This must be a subset of the process affinity mask
        HANDLE hCurrentThread = GetCurrentThread();
        if( INVALID_HANDLE_VALUE != hCurrentThread ) {
            SetThreadAffinityMask(hCurrentThread, dwAffinityMask);
            CloseHandle(hCurrentThread);
        }
    }
	/* --------------------------------
	ハンドルを終了
	-------------------------------- */
    CloseHandle(hCurrentProcess);
}
//=====================================================================//
//                                                                     //
//						現在の時間の取得関数						   //
//                                                                     //
//=====================================================================//
LARGE_INTEGER GetAdjustedCurrentTime(void)
{
	/* --------------------------------
	停止していれば停止時間、そうでなければ現在の時間の取得
	-------------------------------- */
    LARGE_INTEGER time;
	/* --------------------------------
	停止していない
	-------------------------------- */
    if( g_StopTime != 0 ) 
	{
        time.QuadPart = g_StopTime;
    }
	/* --------------------------------
	停止している
	-------------------------------- */
    else 
	{
        QueryPerformanceCounter(&time);
    }
	/* --------------------------------
	時間をリターン
	-------------------------------- */
    return time;
}
