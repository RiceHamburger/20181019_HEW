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
#ifndef INPUT_H_
#define INPUT_H_

#define DIRECTINPUT_VERSION (0x0800)
#include <Windows.h>
#include <dinput.h>
#include <Xinput.h>
//#pragma comment (lib ,"dinput8.dll")
#pragma comment (lib, "xinput.lib")

/**************************************************

定数定義

**************************************************/
#define PAD_VIBRATION_TIME	(250)	//PADコントローラの振動時間

/**************************************************

PADコントローラ構造体

**************************************************/
typedef struct s_controlerState_tag
{
	XINPUT_STATE state;			//PADコントローラの状態
	bool bConnected;			//接続されている状態
}s_controlerState;

/**************************************************

プロトタイプ宣言

**************************************************/

/* --------------------------------
キーボード初期化処理
-------------------------------- */
bool KeyboardInitialize(HINSTANCE hInstance, HWND hWnd);
/* --------------------------------
キーボード終了処理
-------------------------------- */
void KeyboardFinalize(void);
/* --------------------------------
キーボード更新処理
-------------------------------- */
void KeyboardUpdate(void);
/* --------------------------------
DIK_キー関連処理
-------------------------------- */
bool KeyboardIsPress(int nKey);
bool KeyboardIsTrigger(int nKey);
bool KeyboardIsRelease(int nKey);
/* --------------------------------
PADコントローラ初期化処理
-------------------------------- */
void PadInitialize(void);
/* --------------------------------
PADコントローラ更新処理
-------------------------------- */
void PadStateUpdate(void);
/* --------------------------------
PADコントローラ終了処理
-------------------------------- */
void PadStateFinalize(void);
/* --------------------------------
PAD振動処理関連
-------------------------------- */
void SetPadVibration(int uesrNum, bool bIs);
void StopPadVibration(int uesrNum);
bool GetPadVibration(void);
/* --------------------------------
キーの入力処理
-------------------------------- */
void ReadInput(void);
#endif