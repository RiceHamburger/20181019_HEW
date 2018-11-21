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
#include "CActivePillar.h"
#include "COwl.h"
#include "BlockTwoLoop.h"
#include "DoorManager.h"
#include "Result.h"

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
static CActivePillar *pActivePillar;
static CActiveOwl *pActiveOwl;

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
	//オブジェクト管理クラスのインスタンス生成
	m_pObjectMng = new CObjectMng;

	//オブジェクト登録クラスにポインターセット
	CObjectRegister::SetObjectMng(m_pObjectMng);
	// タイトルの点滅ボタン！！
	TitleInit();
	UI_Init();
	ResultInit();
	BackgroundInit();


	PlayerInit();
	//柱の生成
	pPillar = new CPillar(k_kobeni, Float2(810.0f, 577.5f), Float2(55.0f, 107.5f));
	pActivePillar = new CActivePillar(RectC2D(Float2(700.0f, 235.0f), Float2(50.0f, 215.0f)));
	pActiveOwl = new CActiveOwl(Float2(700.0f, 715.0f), Float2(35.0f, 35.0f), k_kobeni, 60);


	//　上手く行けてるもの
	g_kGameStage = k_GAME_INIT;
	Gimmick_ManagerInit();
	CameraManager_Initialize();
	BlockTwoLoopInit();
	Door_Init(k_kobeni);
	SetGameStage(k_GAME_TITLE);
}
//=====================================================================//
//                                                                     //
//							ゲームの終了処理						   //
//                                                                     //
//=====================================================================//
void GameUnit(void)
{
	BackgroundUnit();
	TitleUnit();
	PlayerUnit();
	UI_Unit();
	CameraManager_Finalize();
	Gimmick_ManagerUnit();
	BlockTwoLoopUnit();
	Door_Uninit();
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
		// 再開の時の初期化入れる所
		SetGameStage(k_GAME_TITLE);
		BlockTwoLoopInit();
		Door_Init(k_kobeni);
		break;
	case k_GAME_TITLE:
		break;
	case k_GAME_FADEIN:

		break;
	case k_GAME_TUTORIAL:
		CameraManager_Update(GetPlayerPos(PLAYER_ONE), GetPlayerPos(PLAYER_TWO));


		//オブジェクトの更新
		m_pObjectMng->Update();

		//UI Maneger
		UI_Update();


		//ブロック２の更新処理
		BlockTwoLoopUpdate();
		//ブロック３の更新処理
		Gimmick_ManagerUpdate();
		//ブロック４の更新処理
		Door_Update();

		//*****************************************************************TEST*****************************************************************************************
		SetRange(GetCaneraRange());
		//*****************************************************************TEST*****************************************************************************************

		//終点 ドアー　両方オーペンした場合
		if (Door_Fin()) {
			SetGameStage(k_GAME_RESULT);
		}

		break;
	case k_GAME_START:
		PlayerUpdate();
		break;
	case k_GAME_FADEOUT:

		break;
	case k_GAME_RESULT:
		ResultUpdate(112);
		break;
	case k_GAME_OVER:
		// ゲーム終了の時のリリース処理
		BlockTwoLoopUnit();
		SetGameStage(k_GAME_INIT);
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


		//PlayerDraw();

		//pPillar->Draw();


		//オブジェクトの描画
		m_pObjectMng->Draw();
		//UI描画
		UI_Draw();

		// カメラ処理
		CameraManager_Draw();
		// 背景処理
		BackgroundDraw();
		// ブロック２描画
		BlockTwoLoopDraw();
		// ブロック３描画
		Gimmick_ManagerDraw();
		// ブロック４描画
		Door_Draw();
		break;
	case k_GAME_START:
		PlayerDraw();
		break;
	case k_GAME_FADEOUT:

		break;
	case k_GAME_RESULT:
		// リザルト描画
		ResultDraw();
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
			break;
		case k_GAME_START:

			break;
		case k_GAME_FADEOUT:

			break;
		case k_GAME_RESULT:
			SetGameStage(k_GAME_OVER);
			break;
		case k_GAME_OVER:

			break;
		}
		keyCnt = 3;
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