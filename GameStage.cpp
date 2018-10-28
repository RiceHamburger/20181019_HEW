//=====================================================================//
//		ゲーム更新処理 [gameStage.cpp]                                 //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/07/08            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "GameStage.h"
#include "PlayerManager.h"
#include "cameraManager.h"
#include "Title.h"
#include "TutorialMap.h"
#include "BackgroundManager.h"
#include "UI_Manager.h"
#include "Gimmick_Manager.h"

#include "CObjectMng.h"
#include "CPillar.h"
#include "Gimmick.h"

//=====================================================================//
//                                                                     //
//							 定数定義						           //
//                                                                     //
//=====================================================================//
#define	PLAYER_DEAD	(0)	// プレイヤー死亡　ゲームオーバー
#define CNT_ZERO	(0)
//=====================================================================//
//                                                                     //
//							グローバル変数							   //
//                                                                     //
//=====================================================================//
static k_GAME_STAGE g_kGameStage = k_GAME_INDEX;	// ゲーム進行判定用
static int keyCnt = CNT_ZERO;

static CObjectMng *m_pObjectMng;
static CPillar *pPillar;
//=====================================================================//
//                                                                     //
//							プロトタイプ宣言						   //
//                                                                     //
//=====================================================================//
static void SetGameStage(k_GAME_STAGE gameStage);

//=====================================================================//
//                                                                     //
//							ゲームの初期処理						   //
//                                                                     //
//=====================================================================//
void GameInit(void)
{

	g_kGameStage = k_GAME_INIT;

	//オブジェクト管理クラスのインスタンス生成
	m_pObjectMng = new CObjectMng;

	//オブジェクト登録クラスにポインターセット
	CObjectRegister::SetObjectMng(m_pObjectMng);

	PlayerInit();
	TitleInit();
	//TutorialInit();
	BackgroundInit();
	CameraManager_Initialize();
	//UI
	UI_Init();
	Gimmick_ManagerInit();

	//柱の生成
	pPillar = new CPillar(k_kobeni, Float2(810.0f, 577.5f), Float2(55.0f, 107.5f));
}
//=====================================================================//
//                                                                     //
//							ゲームの終了処理						   //
//                                                                     //
//=====================================================================//
void GameUnit(void)
{
	//TutorialUnit();
	BackgroundUnit();
	TitleUnit();
	PlayerUnit();
	UI_Unit();
	CameraManager_Finalize();
	Gimmick_ManagerUnit();
}

//=====================================================================//
//                                                                     //
//							ゲームの更新処理						   //
//                                                                     //
//=====================================================================//
void GameUpdate(void)
{
	switch (g_kGameStage)
	{
	case k_GAME_INIT:
		SetGameStage(k_GAME_TITLE);
		break;
	case k_GAME_TITLE:
		break;
	case k_GAME_FADEIN:

		break;
	case k_GAME_TUTORIAL:
		//TutorialUpdate();
		//PlayerUpdate();
		CameraManager_Update(GetPlayerPos(PLAYER_ONE), GetPlayerPos(PLAYER_TWO));
		Gimmick_ManagerUpdate();

		//オブジェクトの更新
		m_pObjectMng->Update();

		//UI Maneger
		UI_Update();

		//pPillar->Update();

		//*****************************************************************TEST*****************************************************************************************
		SetRange(GetCaneraRange());
		//*****************************************************************TEST*****************************************************************************************

		//終点
		if (GetPlayerPos(PLAYER_ONE).x > 3600 && GetPlayerPos(PLAYER_TWO).x > 3600) {
			SetGameStage(k_GAME_START);
		}

		break;
	case k_GAME_START:
		PlayerUpdate();
		break;
	case k_GAME_FADEOUT:

		break;
	case k_GAME_RESULT:

		break;
	case k_GAME_OVER:

		break;
	default:
		break;
	}
}
//=====================================================================//
//                                                                     //
//							ゲームの描画処理						   //
//                                                                     //
//=====================================================================//
void GameDraw(void)
{
	switch (g_kGameStage)
	{
	case k_GAME_INIT:

		break;
	case k_GAME_TITLE:
		TitleDraw();
		break;
	case k_GAME_FADEIN:

		break;
	case k_GAME_TUTORIAL:
		CameraManager_Draw();
		//TutorialDraw();
		BackgroundDraw();

		//オブジェクトの描画
		m_pObjectMng->Draw();

		//UI描画
		UI_Draw();

		Gimmick_ManagerDraw();

		//PlayerDraw();
		
		//pPillar->Draw();
		break;
	case k_GAME_START:
		PlayerDraw();
		break;
	case k_GAME_FADEOUT:

		break;
	case k_GAME_RESULT:

		break;
	case k_GAME_OVER:

		break;
	default:
		break;
	}
}
//=====================================================================//
//                                                                     //
//					 セット現在ゲーム進行ステージ					   //
//                                                                     //
//=====================================================================//
void SetGameStage(k_GAME_STAGE gameStage)
{
	g_kGameStage = gameStage;
}
//=====================================================================//
//                                                                     //
//							 セットスタートキー						   //
//                                                                     //
//=====================================================================//
void SetStartKey(void)
{
	if (keyCnt == CNT_ZERO)
	{
		switch (g_kGameStage)
		{
		case k_GAME_INIT:

			break;
		case k_GAME_TITLE:
			SetGameStage(k_GAME_TUTORIAL);
			break;
		case k_GAME_FADEIN:

			break;
		case k_GAME_TUTORIAL:
			//if(TutorialClear())
			//SetGameStage(k_GAME_START);
			break;
		case k_GAME_START:

			break;
		case k_GAME_FADEOUT:

			break;
		case k_GAME_RESULT:

			break;
		case k_GAME_OVER:

			break;
		}
		keyCnt = 20;
	}
	keyCnt = --keyCnt < CNT_ZERO ? CNT_ZERO : keyCnt;
}
//=====================================================================//
//                                                                     //
//							ゲームオーバーの処理				       //
//                                                                     //
//=====================================================================//
bool GameOverCheck(void)
{
	return false;
}