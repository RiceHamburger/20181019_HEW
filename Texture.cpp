//=====================================================================//
//		テクスチャ処理 [texture.cpp]                                   //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/07/05            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "Texture.h"


//=====================================================================//
//                                                                     //
//                           テクスチャ							       //
//                                                                     //
//=====================================================================//
static const textureData textureFiles[] =
{
	{ "asset/texture/title.jpg",				1000,	800	},		// indexのため　使わない
	{ "asset/texture/title.jpg",				1000,	800 },		// タイトル
	{ "asset/texture/kobeni.png",				512,	512 },		// kobeni
	{ "asset/texture/sozai1.jpg",				3200,	900},		// タイトル
	{ "asset/texture/heart.png",				32,		32 },		// 生命力
	{ "asset/texture/playerLifeBG.jpg",			70,		900 },		// 生命力の背景
	{ "asset/texture/ladder.jpg",				77,		431 },		// はしご
	{ "asset/texture/TimeNum.png",				320,	42 },		// ランキング用ナンバー
	{ "asset/texture/ranking.png",				1600,	900 },		// ランキング
}; 

/* --------------------------------

配列サイズの計ると個数分が出る ARRAYSIZEも同じ効果
static const int TEXTURE_NUM_MAX = sizeof(textureFiles) / sizeof(textureFiles[0]);

-------------------------------- */
static const int TEXTURE_NUM_MAX = ARRAYSIZE(textureFiles);
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_NUM_MAX];

//=====================================================================//
//                                                                     //
//						テクスチャ読み込み関数					       //
//                                                                     //
//=====================================================================//
int TextrueInit(void)
{
	/* --------------------------------
	デバイスなどゲット
	-------------------------------- */
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();
	/* --------------------------------
	読み込み失敗数
	-------------------------------- */
	int failedCount = 0;

	for (int i = 0; i < TEXTURE_NUM_MAX; i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, textureFiles[i].textureName, &g_pTextures[i]);
		if (FAILED(hr))
		{
			/* --------------------------------
			読めなかった数
			-------------------------------- */
			failedCount++;
		}
	}
	/* --------------------------------
	リターン読めなかった数
	-------------------------------- */
	return failedCount;
}

//=====================================================================//
//                                                                     //
//						テクスチャの終了処理関数				       //
//                                                                     //
//=====================================================================//
void TextrueUnit(void)
{
	/* --------------------------------
	テクスチャの開放
	-------------------------------- */
	for (int i = 0; i < TEXTURE_NUM_MAX; i++)
	{
		if (g_pTextures[i] != NULL)
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}
//=====================================================================//
//                                                                     //
//						ゲットテクスチャの描画関数				       //
//                                                                     //
//=====================================================================//
LPDIRECT3DTEXTURE9 DirectX3DGetTEXTURE(int index)
{
	/* --------------------------------
	リターン指定したテクスチャ
	-------------------------------- */
	return g_pTextures[index];
}
int TextrueGetWidth(int index)
{
	/* --------------------------------
	リターン指定したテクスチャ幅
	-------------------------------- */
	return textureFiles[index].width;
}
int TextrueGetHeight(int index)
{
	/* --------------------------------
	リターン指定したテクスチャ高さ
	-------------------------------- */
	return textureFiles[index].height;
}