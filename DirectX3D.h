//=====================================================================//
//		デバイス処理 [directX3D.h]								       //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/05/15            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#ifndef DIRECTX3D_H
#define DIRECTX3D_H

#include <Windows.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


/**************************************************

レンダリング用enum

**************************************************/
typedef enum k_RENDER_STATE_tag
{
	k_RENDER_INDEX,			// インデックス
	k_RENDER_DEFAULT,		// デフォルト(不透明)
	k_RENDER_ALPHATEST,		// αテスト
	k_RENDER_HALFADD,		// 半加算合成
	k_RENDER_ADD,			// 加算合成
	k_RENDER_MAX,			// インデックスマックス
}k_RENDER_STATE;

/**************************************************

プロトタイプ宣言

**************************************************/

/* --------------------------------
D3Dデバイス初期化処理
戻り値:初期化に失敗したらFALSE
引数:hWnd....ウィンドウハンドル
-------------------------------- */
bool DirectX3DInitialize(HWND hWnd);
/* --------------------------------
D3Dデバイス終了処理
-------------------------------- */
void DirectX3DFinalize(void);
/* --------------------------------
D3Dデバイスポインターの取得
-------------------------------- */
LPDIRECT3DDEVICE9 DirectX3DGetDevice(void);
/* --------------------------------
テクスチャの取得
-------------------------------- */
LPDIRECT3DTEXTURE9 DirectX3DGetTEXTURE(HWND hWnd, LPCSTR address);

void SetRenderState(k_RENDER_STATE RenderState);

#endif //DIRECTX3D_H