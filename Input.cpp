//=====================================================================//
//		入力処理 [input.h]                                             //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/07/05            //
//   2018/08/03  ver2.0                                                //
//   追加コントローラパッド機能                                        //
//   2018/10/06  ver3.0                                                //
//   コントローラパッド複数追加                                        //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "Input.h"
#include "GameStage.h"
#include "CPlayer.h"
#include "PlayerManager.h"
#include "Gimmick_Manager.h"
#include "DoorManager.h"
#include "BlockTwoLoop.h"

//=====================================================================//
//                                                                     //
//							 定数定義						           //
//                                                                     //
//=====================================================================//
#define	NUM_KEY_MAX						(256)					// キーの最大数

#define VALUE_ZERO						(0)						// 移動量、振動量ゼロ
#define VALUE_MAX						(65535)					// 移動量、振動量最大値

#define MAX_CONTROLLERS					(4)						// XInputが認識できるのは4つまで
#define CONTROLLER_USER_1				(0)						// コントローラユーザー １
#define CONTROLLER_USER_2				(1)						// コントローラユーザー 2
#define THRESHOLD						(65536 / 4)				// PADアナログボタンのしきい値
#define THRESHOLD_TRIGGER				(255 / 2)				// PADアナログボタンのしきい値														   

//=====================================================================//
//                                                                     //
//							プロトタイプ宣言						   //
//                                                                     //
//=====================================================================//
static bool initialize(HINSTANCE hInstance);					//DXinput、Xinputの初期処理
static void finalize(void);										//DXinput、Xinputの終了処理

//=====================================================================//
//                                                                     //
//							グローバル変数							   //
//                                                                     //
//=====================================================================//
static LPDIRECTINPUT8		g_pInput = NULL;					// DirectInputオブジェクトへのポインタ
static LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// 入力デバイス(キーボード)へのポインタ
static BYTE					g_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
static BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
static BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク

static s_controlerState		GAME_PAD[MAX_CONTROLLERS];			// XInput PAD構造体
static WORD					g_buttons;							// PADの入力情報ワーク
static XINPUT_VIBRATION		g_vibration[MAX_CONTROLLERS];		// PADの振動情報ワーク
static bool					g_xinputVibrationCheck[MAX_CONTROLLERS] = { false };		// PADの振動状態
																
//=====================================================================//
//                                                                     //
//							入力処理の初期化						   //
//                                                                     //
//=====================================================================//
bool initialize(HINSTANCE hInstance)
{
	/* --------------------------------
	DXinput新規作成
	-------------------------------- */
	if (g_pInput == NULL)
	{
		/* --------------------------------
		DirectInputオブジェクトの作成
		-------------------------------- */
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) {
			return false;
		}
	}
	/* --------------------------------
	Xinput PADコントローラ初期化
	-------------------------------- */
	PadInitialize();

	return true;
}

//=====================================================================//
//                                                                     //
//							入力処理の終了処理						   //
//                                                                     //
//=====================================================================//
void finalize(void)
{
	/* --------------------------------
	Xinput PADコントローラ停止（振動など）
	-------------------------------- */
	PadStateFinalize();
	/* --------------------------------
	DXinput メモリ解放
	-------------------------------- */
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=====================================================================//
//                                                                     //
//							キーボードの初期化						   //
//                                                                     //
//=====================================================================//
bool KeyboardInitialize(HINSTANCE hInstance, HWND hWnd)
{
	/* --------------------------------
	入力処理の初期化
	-------------------------------- */
	if (!initialize(hInstance))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return false;
	}
	/* --------------------------------
	デバイスの作成
	-------------------------------- */
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return false;
	}
	/* --------------------------------
	データフォーマットを設定
	-------------------------------- */
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return false;
	}
	/* --------------------------------
	協調モードを設定（フォアグラウンド＆非排他モード）
	-------------------------------- */
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_EXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return false;
	}
	/* --------------------------------
	キーボードへのアクセス権を獲得(入力制御開始)
	-------------------------------- */
	g_pDevKeyboard->Acquire();

	/* --------------------------------
	設定完了するとリターンtrue
	-------------------------------- */
	return true;
}

//=====================================================================//
//                                                                     //
//						キーボードの終了処理						   //
//                                                                     //
//=====================================================================//
void KeyboardFinalize(void)
{
	/* --------------------------------
	入力デバイス(キーボード)のメモリ開放
	キーボードへのアクセス権を開放(入力制御終了)
	メモリ開放
	-------------------------------- */
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	/* --------------------------------
	入力処理の終了処理
	-------------------------------- */
	finalize();
}

//=====================================================================//
//                                                                     //
//						キーボードの更新処理						   //
//                                                                     //
//=====================================================================//
void KeyboardUpdate(void)
{
	/* --------------------------------
	キーのバッファー
	-------------------------------- */
	BYTE aKeyState[NUM_KEY_MAX];

	/* --------------------------------
	デバイスからデータを取得
	-------------------------------- */
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		// aKeyState[DIK_SPACE] & 0x80 記録用
		/* --------------------------------
		ループ処理
		-------------------------------- */
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			/* --------------------------------
			キートリガー・リリース情報を生成
			-------------------------------- */
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];

			/* --------------------------------
			キープレス情報を保存
			-------------------------------- */
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		/* --------------------------------
		キーボードへのアクセス権を取得
		-------------------------------- */
		g_pDevKeyboard->Acquire();
	}

	/* --------------------------------
	左移動	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_LEFT) || KeyboardIsPress(DIK_A))
	{
		SetPlayerMove(PLAYER_ONE , false);
	}
	/* --------------------------------
	右移動	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_RIGHT) || KeyboardIsPress(DIK_D))
	{
		SetPlayerMove(PLAYER_ONE , true);
	}
	/* --------------------------------
	上移動	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_UP) || KeyboardIsPress(DIK_W))
	{
		if (GetPlayerClimb(PLAYER_ONE)) {
			SetPlayerMoveY(PLAYER_ONE, true);
		}
	}
	/* --------------------------------
	下移動	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_DOWN) || KeyboardIsPress(DIK_S))
	{
		if (GetPlayerClimb(PLAYER_ONE)) {
			SetPlayerMoveY(PLAYER_ONE, false);
		}
	}
	/* --------------------------------
	スペースキー	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_SPACE))
	{
		SetPlayerJump(PLAYER_ONE);
	}
	/* --------------------------------
	左移動	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_J))
	{
		SetPlayerMove(PLAYER_TWO , false);
	}

	/* --------------------------------
	右移動	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_L))
	{
		SetPlayerMove(PLAYER_TWO , true);
	}
	/* --------------------------------
	上移動	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_I))
	{
		if (GetPlayerClimb(PLAYER_TWO)) {
			SetPlayerMoveY(PLAYER_TWO, true);
		}
	}
	/* --------------------------------
	下移動	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_K))
	{
		if (GetPlayerClimb(PLAYER_TWO)) {
			SetPlayerMoveY(PLAYER_TWO, false);
		}
	}
	/* --------------------------------
	ジャンプ	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_M))
	{
		SetPlayerJump(PLAYER_TWO);
	}


	/* --------------------------------
	武器１
	-------------------------------- */
	if (KeyboardIsPress(DIK_Z) || KeyboardIsPress(DIK_J))
	{
		Door_Switch(PLAYER_TWO);
	}
	/* --------------------------------
	武器２
	-------------------------------- */
	if (KeyboardIsRelease(DIK_X) || KeyboardIsRelease(DIK_K))
	{
		Door_Switch(PLAYER_ONE);
	}
	/* --------------------------------
	武器SP
	-------------------------------- */
	if (KeyboardIsPress(DIK_SPACE) || KeyboardIsPress(DIK_L))
	{

	}
	/* --------------------------------
	エンターキー
	-------------------------------- */
	if (KeyboardIsRelease(DIK_RETURN))
	{
		SetStartKey();
	}

	/* --------------------------------
	アクション1
	-------------------------------- */
	if (KeyboardIsPress(DIK_Z))
	{
		BlockTwoSwitch();
	}
}


//=====================================================================//
//                                                                     //
//					キーボードのプレス状態を取得					   //
//                                                                     //
//=====================================================================//
bool KeyboardIsPress(int nKey)
{
	/* --------------------------------
	リターンキー情報
	-------------------------------- */
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}


//=====================================================================//
//                                                                     //
//					キーボードのトリガー状態を取得					   //
//                                                                     //
//=====================================================================//
bool KeyboardIsTrigger(int nKey)
{
	/* --------------------------------
	リターンキー情報
	-------------------------------- */
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=====================================================================//
//                                                                     //
//					キーボードのリリ－ス状態を取得					   //
//                                                                     //
//=====================================================================//
bool KeyboardIsRelease(int nKey)
{
	/* --------------------------------
	リターンキー情報
	-------------------------------- */
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//=====================================================================//
//                                                                     //
//						PADコントローラの初期化						   //
//                                                                     //
//=====================================================================//
void PadInitialize(void)
{


	/* --------------------------------
	PADコントローラ読み込む
	一時用変数宣言
	-------------------------------- */
	DWORD dwResult;

	/* --------------------------------
	接続されているPAD個数を調べる
	-------------------------------- */
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		/* --------------------------------
		状態取得
		-------------------------------- */
		dwResult = XInputGetState(i, &GAME_PAD[i].state);

		/* --------------------------------
		接続している
		-------------------------------- */
		if (dwResult == ERROR_SUCCESS)
		{
			GAME_PAD[i].bConnected = true;
			/* --------------------------------
			PADコントローラ振動初期化
			-------------------------------- */
			g_xinputVibrationCheck[i] = false;
		}
		/* --------------------------------
		接続していない
		-------------------------------- */
		else
		{
			GAME_PAD[i].bConnected = false;
		}
	}
}

//=====================================================================//
//                                                                     //
//						PADコントローラの終了処理					   //
//                                                                     //
//=====================================================================//
void PadStateFinalize(void)
{
	/* --------------------------------
	PADコントローラ使用停止
	-------------------------------- */
	XInputEnable(false);
}
//=====================================================================//
//                                                                     //
//						PADユーザー別の更新処理						   //
//                                                                     //
//=====================================================================//
void PadUserUpdate(int userNum)
{
	/* --------------------------------
	PADコントローラ状態取得
	キーの情報取得
	-------------------------------- */
	XInputGetState(userNum, &GAME_PAD[userNum].state);
	g_buttons = GAME_PAD[userNum].state.Gamepad.wButtons;

	/* --------------------------------
	上
	-------------------------------- */
	if (GAME_PAD[userNum].state.Gamepad.sThumbLY >= THRESHOLD)
	{

	}
	/* --------------------------------
	下
	-------------------------------- */
	if (GAME_PAD[userNum].state.Gamepad.sThumbLY <= -THRESHOLD)
	{

	}
	/* --------------------------------
	左
	-------------------------------- */
	if (GAME_PAD[userNum].state.Gamepad.sThumbLX <= -THRESHOLD)
	{
		SetPlayerMove(userNum, false);
	}
	/* --------------------------------
	右
	-------------------------------- */
	if (GAME_PAD[userNum].state.Gamepad.sThumbLX >= THRESHOLD)
	{
		SetPlayerMove(userNum, true);
	}
	/* --------------------------------
	ジャンプ
	-------------------------------- */
	if (g_buttons & XINPUT_GAMEPAD_A)
	{
		SetPlayerJump(userNum);
	}

	/* --------------------------------
	スタートぼたん
	-------------------------------- */
	if (g_buttons & XINPUT_GAMEPAD_START)
	{
		SetStartKey();
	}

}


//=====================================================================//
//                                                                     //
//						PADコントローラの更新処理					   //
//                                                                     //
//=====================================================================//
void PadStateUpdate(void)
{
	PadUserUpdate(CONTROLLER_USER_1);
	PadUserUpdate(CONTROLLER_USER_2);
	/*
					**********     制御 コピペ用     **********
	//アナログ方向キー
	if (GAME_PAD[i].state.Gamepad.sThumbLY > Threshold)
	if (GAME_PAD[i].state.Gamepad.sThumbLY < -Threshold)
	if (GAME_PAD[i].state.Gamepad.sThumbLX > Threshold)
	if (GAME_PAD[i].state.Gamepad.sThumbLX < -Threshold)

	//デジタル方向キー
	if (g_buttons & XINPUT_GAMEPAD_DPAD_UP)
	if (g_buttons & XINPUT_GAMEPAD_DPAD_DOWN)
	if (g_buttons & XINPUT_GAMEPAD_DPAD_LEFT)
	if (g_buttons & XINPUT_GAMEPAD_DPAD_RIGHT)

	//各種ボタン 空制御
	if (g_buttons & XINPUT_GAMEPAD_A);
	if (g_buttons & XINPUT_GAMEPAD_B);
	if (g_buttons & XINPUT_GAMEPAD_X);
	if (g_buttons & XINPUT_GAMEPAD_Y);
	if (g_buttons & XINPUT_GAMEPAD_START);
	if (g_buttons & XINPUT_GAMEPAD_BACK);
	if (g_buttons & XINPUT_GAMEPAD_LEFT_THUMB);//左アナログ方向キーをパッド奥に押した場合
	if (g_buttons & XINPUT_GAMEPAD_RIGHT_THUMB);//右アナログ方向キーをパッド奥に押した場合
	if (g_buttons & XINPUT_GAMEPAD_LEFT_SHOULDER);
	if (g_buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
	if (GAME_PAD[i].state.Gamepad.bLeftTrigger);
	if (GAME_PAD[i].state.Gamepad.bRightTrigger);

	//振動セット
	XInputSetState(0, &g_vibration);
	*/
}

//=====================================================================//
//                                                                     //
//					セットPADコントローラの振動状態					   //
//                                                                     //
//=====================================================================//
void SetPadVibration(int uesrNum, bool bIs)
{
	/* --------------------------------
	振動していないと　振動セット
	-------------------------------- */
	if (!g_xinputVibrationCheck)
	{
		g_xinputVibrationCheck[uesrNum] = bIs;
		g_vibration[uesrNum].wLeftMotorSpeed = g_vibration[uesrNum].wRightMotorSpeed = VALUE_MAX;
		XInputSetState(uesrNum, &g_vibration[uesrNum]);
	}
}

//=====================================================================//
//                                                                     //
//					 停止PADコントローラの振動状態					   //
//                                                                     //
//=====================================================================//
void StopPadVibration(int uesrNum)
{
	/* --------------------------------
	停止振動
	-------------------------------- */
	SetPadVibration(uesrNum, true);
	g_xinputVibrationCheck[uesrNum] = false;
	g_vibration[uesrNum].wLeftMotorSpeed = g_vibration[uesrNum].wRightMotorSpeed = VALUE_ZERO;
	XInputSetState(uesrNum, &g_vibration[uesrNum]);
}
//=====================================================================//
//                                                                     //
//					ゲットPADコントローラの振動状態					   //
//                                                                     //
//=====================================================================//
bool GetPadVibration(void)
{
	/* --------------------------------
	リターン現在の振動状態
	-------------------------------- */
	if (g_xinputVibrationCheck[CONTROLLER_USER_1] && g_xinputVibrationCheck[CONTROLLER_USER_2])
		return true;
}


//=====================================================================//
//                                                                     //
//								input実行						       //
//                                                                     //
//=====================================================================//
void ReadInput(void)
{
	/* --------------------------------
	キーボードの更新処理
	-------------------------------- */
	KeyboardUpdate();
	PadStateUpdate();
}
