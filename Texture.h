//=====================================================================//
//		テクスチャ処理 [texture.h]                                     //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/07/05            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#ifndef TEXTRUE_H_
#define TEXTRUE_H_
#include "DirectX3D.h"

/**************************************************

定数定義

**************************************************/
#define		TEXTURE_FILENAME_MAX	(64)		//ファイルの名前の長さ

/**************************************************

		テクスチャファイル対応用enum

**************************************************/
typedef enum k_Texture_tag
{
	E_TEXTURE_INDEX = 0,
	k_title,
	k_kobeni,
	k_tutorialMap,
	k_playerLife,
	k_playerLifeBG,
	k_ladder,
	k_timerank,
	k_rank,
	E_TEXTURE_MAX,
}k_Texture;

/**************************************************

			テクスチャデータ構造体

**************************************************/
typedef struct textureData_tag
{
	char textureName[TEXTURE_FILENAME_MAX];	// テキスチャー
	int width;		   // 長さ
	int height;		   // 高さ
}textureData;

/**************************************************

プロトタイプ宣言

**************************************************/

/* --------------------------------
テクスチャ読み込む処理
-------------------------------- */
int TextrueInit(void);
/* --------------------------------
ゲットテクスチャ幅
-------------------------------- */
int TextrueGetWidth(int index);
/* --------------------------------
ゲットテクスチャ高さ
-------------------------------- */
int TextrueGetHeight(int index);
/* --------------------------------
テクスチャ終了処理
-------------------------------- */
void TextrueUnit(void);
/* --------------------------------
ゲットテクスチャ
-------------------------------- */
LPDIRECT3DTEXTURE9 DirectX3DGetTEXTURE(int index);

#endif // !TEXTRUE_H_
