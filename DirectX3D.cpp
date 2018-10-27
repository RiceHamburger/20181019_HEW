//=====================================================================//
//		デバイス処理 [directX3D.cpp]								   //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/05/15            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "DirectX3D.h"
#include "Config.h"

//=====================================================================//
//                                                                     //
//                       グローバル変数宣言						       //
//                                                                     //
//=====================================================================//
static LPDIRECT3D9 g_pD3D = NULL;				//Direct3 インタフェース
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Device9 デバイスのID
static LPDIRECT3DTEXTURE9 g_pTexture = NULL;	//テクスチャ保存場所

//=====================================================================//
//                                                                     //
//                       引数:hWnd....ウィンドウハンドル		       //
//                                                                     //
//=====================================================================//
bool DirectX3DInitialize(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//DX9のデイパスを取得
	D3DPRESENT_PARAMETERS g_d3dpp = {};			//デバイスの動作を設定する構造体
	g_d3dpp.BackBufferWidth = SCREEN_WIDTH;
	g_d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.BackBufferCount = 1;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//スワップ　エフェクト
	g_d3dpp.Windowed = TRUE;					//!!フルースクリーンはここを修正!!
	g_d3dpp.EnableAutoDepthStencil = TRUE;		//3D時に前と後ろの判定
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//D24S8 Depthバッファ16ビット確保する

	//フルースクリーンじゃない時意味がない
	//モニターに対応するHzを入れないとダメ
	g_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	HRESULT hr = g_pD3D->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&g_d3dpp,
		&g_pD3DDevice
	);
	if (FAILED(hr))
	{
		hr = g_pD3D->CreateDevice
		(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&g_d3dpp,
			&g_pD3DDevice
		);
		if (FAILED(hr))
		{
			hr = g_pD3D->CreateDevice
			(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&g_d3dpp,
				&g_pD3DDevice
			);
		}
		if (FAILED(hr))
		{
			//取得失敗
			MessageBox(NULL, FAILED_MESSAGE, FAILED_MESSAGE_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1);
		}
		if (FAILED(hr))
		{
			return false;
		}


	}
	//横サンプラー
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//縦サンプラー
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	////拡大
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	//縮小
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	//ミップマップ
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	//アルファ設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//ポリゴンのアルファ設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	return true;
}

//=====================================================================//
//                                                                     //
//							    終了処理						       //
//                                                                     //
//=====================================================================//
void DirectX3DFinalize(void)
{
	/* --------------------------------
	デバイス開放
	-------------------------------- */
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	/* --------------------------------
	DX開放
	-------------------------------- */
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=====================================================================//
//                                                                     //
//						D3Dデバイスポインターの取得				       //
//                                                                     //
//=====================================================================//
LPDIRECT3DDEVICE9 DirectX3DGetDevice(void)
{
	/* --------------------------------
	リターンデバイス
	-------------------------------- */
	return g_pD3DDevice;
}

//=====================================================================//
//                                                                     //
//							テクスチャの取得					       //
//                                                                     //
//=====================================================================//
LPDIRECT3DTEXTURE9 DirectX3DGetTEXTURE(HWND hWnd, LPCSTR address)
{
	/* --------------------------------
	リターンテクスチャ
	-------------------------------- */
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, address, &g_pTexture)))
	{
		MessageBox(hWnd, "テクスチャファイル読み込み失敗", FAILED_MESSAGE_TITLE, MB_OKCANCEL | MB_DEFBUTTON2);
	}
	return g_pTexture;
}

//=====================================================================//
//                                                                     //
//                          レンダー変更用                             //
//                                                                     //
//=====================================================================//
// レンダーステートの変更
void SetRenderState(k_RENDER_STATE RenderState)
{
	/* --------------------------------
	レンダリング指定用
	-------------------------------- */
	switch (RenderState)
	{
	/* --------------------------------
	レンダリング　デフォルト
	-------------------------------- */
	case k_RENDER_DEFAULT:
	{
		// 不透明オブジェクト
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			//アルファブレンディングの無効化
	}
	break;
	/* --------------------------------
	レンダリング　透明
	-------------------------------- */
	case k_RENDER_ALPHATEST:
	{
		// αテストによる透明領域の切り抜き
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//ブレンディングオプション加算
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
	}
	break;
	/* --------------------------------
	レンダリング　半加算
	-------------------------------- */
	case k_RENDER_HALFADD:
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//アルファブレンディングの有効化
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				//Zバッファへの書き込みを無効にする。
		
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//ブレンディングオプション加算
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//SRCの設定
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DESTの設定

	}
	break;
	/* --------------------------------
	レンダリング　フルー加算合成
	-------------------------------- */
	case k_RENDER_ADD:
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//アルファブレンディングの有効化
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//ブレンディングオプション加算
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);			//SRCの設定
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DESTの設定
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
	}
	break;
	}
}