//=====================================================================//
//		チュートリアル [TutorialMap.cpp]                               //
//                                                                     //
//                                               SoSei				   //
//                                               2018/10/06            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "TutorialMap.h"
#include "DirectX3D.h"
#include "Texture.h"
#include "Config.h"

//=====================================================================//
//                                                                     //
//                       グローバル変数宣言						       //
//                                                                     //
//=====================================================================//
static bool g_tutorialClear = false;
static CTutorialMap* g_pTutorialMap = NULL;
static float g_mapUNum = 0;
/* --------------------------------
チュートリアルの初期処理
-------------------------------- */
void TutorialInit(void)
{
	g_pTutorialMap = new CTutorialMap;
}
/* --------------------------------
チュートリアルの終了処理
-------------------------------- */
void TutorialUnit(void)
{
	PTR_DELETE(g_pTutorialMap);
}
/* --------------------------------
チュートリアルの描画処理
-------------------------------- */
void TutorialDraw(void)
{
	g_pTutorialMap->CDraw();
}
/* --------------------------------
チュートリアルの更新処理
-------------------------------- */
void TutorialUpdate(void)
{
	if (g_mapUNum > 1.225)
	{
		g_tutorialClear = true;
		return;
	}
	g_mapUNum += 0.0025f;
	g_pTutorialMap->SetUVNum(g_mapUNum, 0);
}

/* --------------------------------
クリア可能
-------------------------------- */
bool TutorialClear(void)
{
	return g_tutorialClear;
}


//******************************   チュートリアル用クラス設定   ******************************//
CTutorialMap::CTutorialMap()
{
	//初期化
	SetPos(D3DXVECTOR2(400.0f, 450.0f), 1600, 900);
	SetDivide(2, 1);
	SetUVNum(0, 0);
	m_pDevice = DirectX3DGetDevice();
	m_pTex = DirectX3DGetTEXTURE(k_tutorialMap);
}
CTutorialMap::~CTutorialMap()
{
	m_pTex->Release();
	m_pTex = NULL;
	m_pDevice = NULL;
}
void CTutorialMap::CDraw(void)
{
	Draw(m_pDevice, m_pTex);
}