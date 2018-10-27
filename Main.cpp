//=====================================================================//
//		メイン処理 [mian.cpp]                                          //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/05/05            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "Config.h"
#include "DirectX3D.h"
#include "SystemTimer.h"
#include "GameStage.h"
#include "Input.h"

//=====================================================================//
//                                                                     //
//                      グローバル変数宣言                             //
//                                                                     //
//=====================================================================//
/* --------------------------------
ウィンドウ宣言
-------------------------------- */
HWND hWnd = NULL;
/* --------------------------------
FPS計測用
-------------------------------- */
static double g_ReserveTime = CNT_ZERO;

//=====================================================================//
//                                                                     //
//                       プロトタイプ宣言                              //
//                                                                     //
//=====================================================================//
/* --------------------------------
ウインドウプロシージャ(コールバック関数)
-------------------------------- */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/* --------------------------------
ゲームの初期化関数
ゲームの更新関数
ゲームの描画関数
ゲームの終了処理
-------------------------------- */
static bool Initialize(HINSTANCE hInstance, HWND hWnd);
static void Update(void);
static void Draw(void);
static void Finalize(void);


//*********************************************************************//
//                                                                     //
//                            main関数                                 //
//                                                                     //
//*********************************************************************//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);					//使ってない
	UNREFERENCED_PARAMETER(lpCmdLine);						//使ってない

	WNDCLASS wc			= {};								//ウィンドウクラス初期化(0が入る)
	wc.lpfnWndProc		= WndProc;							//ウィンドウプロシージャ
	wc.lpszClassName	= CLASS_NAME;						//クラス名
	wc.hInstance		= hInstance;						//hInstanceハンドルID
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);		//マウスカーソル復帰
	wc.hbrBackground	= (HBRUSH)(COLOR_BACKGROUND + 1);	//背景色 設定値＋１

	RegisterClass(&wc);										//システムにクラスを登録

	//*************************     screen設定     *************************//
	//希望画面サイズ	マジックナンバーはよくない
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; 

	//外枠ある時の画面サイズ　AdjustWindowRect枠サイズ計算
	AdjustWindowRect(&window_rect, WINDOW_STYLE, FALSE);

	int screenWidth	 = window_rect.right - window_rect.left;
	int screenHeight = window_rect.bottom - window_rect.top;

	//プライマリーモニターdesktop画面サイズ獲得
	int screenWidthDesktop	= GetSystemMetrics(SM_CXSCREEN);
	int screenHeightDesktop = GetSystemMetrics(SM_CYSCREEN);

	//画面真ん中に表示するXY位置計算
	int screenPosX = (int)((screenWidthDesktop  - screenWidth) / 2);
	int screenPosY = (int)((screenHeightDesktop - screenHeight) / 2);

	//max(a,b)  大きかったものをreturn minもある
	//max()を封印したかったら #define NOMINMAX
	screenPosX = max(screenPosX, 0);
	screenPosY = max(screenPosY, 0);

		hWnd = CreateWindow(
		CLASS_NAME,							//ウィンドウクラス名
		WINDOW_CAPTION,						//キャプション
		WINDOW_STYLE,						//ウインドウスタイルフラグ（ビット）
		screenPosX,							//ウインドウ座標X (左上から) CW_USEDEFAULT	
		screenPosY,							//ウインドウ座標Y　CW_USEDEFAULT
		screenWidth,						//ウインドウ幅 CW_USEDEFAULT
		screenHeight,						//ウインドウ高さ CW_USEDEFAULT
		NULL,								//親ウインドウ
		NULL,								//メニュ
		hInstance,							//hInstanceハンドルID
		NULL								//ウインドウメッセージで送れるオリジナルデータなどのポインター
	);

	ShowWindow(hWnd, nCmdShow);				//ウインドウ表示関数
	UpdateWindow(hWnd);

	//*************************     ゲーム＆Direct3Dの初期化     *************************//
	if (!Initialize(hInstance, hWnd))
	{
		//初期化失敗した
		return -1;
	}
	

	MSG msg = {};									//メッセージクラスを定義　処理用ため
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//ゲットメッセージ関数(マウスとキー)
		{
			TranslateMessage(&msg);					 //キー入力のメッセージを加工
			DispatchMessage(&msg);					 //メッセージをウインドウプロシージャ 自動スキャン下のCALLBACK
		}
		else
		{
			//*************************       FPS計測処理      ************************* //
			double time = SystemTimerGetTime();
			if ((time - g_ReserveTime) < 1.0f / 60.0f)
			{
				continue;
			}
			g_ReserveTime = time;
			//*************************     ゲーム入力処理     ************************* /
			ReadInput();
			//*************************     ゲーム更新処理     ************************* //
			Update();
			//*************************     ゲーム描画処理     ************************* //
			Draw();

		}
	} while (msg.message != WM_QUIT);

	//*************************     ゲーム＆Direct3D終了処理     ************************* //
	Finalize();

	return (int)msg.wParam;
}

//=====================================================================//
//                                                                     //
//							ゲームの回帰関数					       //
//                                                                     //
//=====================================================================//
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_TIMER:
		//switch (wParam)
		//{
		////case TC_TIMER01:
		////	break;
		//default:
		//	break;
		//}
		break;
	case WM_KEYDOWN:
		if (wParam == WM_KEYDOWN)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_POWERBROADCAST:
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		/* --------------------------------
		タイマーの終了処理
		-------------------------------- */
		//DestoryTimer(hWnd, TC_TIMER01);
		PostQuitMessage(0);
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=====================================================================//
//                                                                     //
//							ゲームの初期化関数					       //
//                                                                     //
//=====================================================================//
bool Initialize(HINSTANCE hInstance, HWND hWnd)
{
	/* --------------------------------
	D3D初期化
	-------------------------------- */
	if (!DirectX3DInitialize(hWnd))
	{
		return false;
	}
	/* --------------------------------
	キーボード入力初期化
	-------------------------------- */
	if (!KeyboardInitialize(hInstance, hWnd))
	{
		return false;
	}
	/* --------------------------------
	テクスチャセット
	-------------------------------- */
	if (TextrueInit() > 0)
	{
		MessageBox(hWnd, "テクスチャファイル読み込み失敗", FAILED_MESSAGE_TITLE, MB_OKCANCEL | MB_DEFBUTTON2);
		return false;
	}
	/* --------------------------------
	ゲッターテスト
	-------------------------------- */
	if (!DirectX3DGetDevice())
	{
		return false;
	}
	/* --------------------------------
	ゲームの初期化
	-------------------------------- */
	GameInit();

	return true;
}

//=====================================================================//
//                                                                     //
//							ゲームの更新関数					       //
//                                                                     //
//=====================================================================//
void Update(void)
{
	/* --------------------------------
	ステージ別処理
	-------------------------------- */
	GameUpdate();
	return;
}

//=====================================================================//
//                                                                     //
//							ゲームの描画関数					       //
//                                                                     //
//=====================================================================//
void Draw(void)
{
	/* --------------------------------
	ゲットデバイス
	-------------------------------- */
	LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();

	/* --------------------------------
	デバイス CLear(0は全部消す,NULL, 画面の色|深さデータ, 色, 0は手前1は奥,D3DCLEAR_STENCILを指定する場合使う )
	-------------------------------- */
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 100, 100, 255), 1.0f, 0);

	//*************************     描画開始     ************************* //
	pDevice->BeginScene();

	/* --------------------------------
	初期描画透明セット
	ステージ描画別処理
	-------------------------------- */
	SetRenderState(k_RENDER_ALPHATEST);
	GameDraw();

	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);
	//*************************     描画終了     ************************* //
}
//=====================================================================//
//                                                                     //
//						ゲームの終了処理関数					       //
//                                                                     //
//=====================================================================//
void Finalize(void)
{
	/* --------------------------------
	ゲームの終了
	-------------------------------- */
	GameUnit();
	TextrueUnit();
	return;
}