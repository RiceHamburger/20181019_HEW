//=====================================================================//
//		�Q�[���X�V���� [gameStage.cpp]                                 //
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
//							 �萔��`						           //
//                                                                     //
//=====================================================================//
#define	PLAYER_DEAD	(0)	// �v���C���[���S�@�Q�[���I�[�o�[
#define CNT_ZERO	(0)
//=====================================================================//
//                                                                     //
//							�O���[�o���ϐ�							   //
//                                                                     //
//=====================================================================//
static k_GAME_STAGE g_kGameStage = k_GAME_INDEX;	// �Q�[���i�s����p
static int keyCnt = CNT_ZERO;

static CObjectMng *m_pObjectMng;
static CPillar *pPillar;
static CActivePillar *pActivePillar;
static CActiveOwl *pActiveOwl;

//=====================================================================//
//                                                                     //
//							�v���g�^�C�v�錾						   //
//                                                                     //
//=====================================================================//
static void SetGameStage(k_GAME_STAGE gameStage);

//=====================================================================//
//                                                                     //
//							�Q�[���̏�������						   //
//                                                                     //
//=====================================================================//
void GameInit(void)
{

	g_kGameStage = k_GAME_INIT;

	//�I�u�W�F�N�g�Ǘ��N���X�̃C���X�^���X����
	m_pObjectMng = new CObjectMng;

	//�I�u�W�F�N�g�o�^�N���X�Ƀ|�C���^�[�Z�b�g
	CObjectRegister::SetObjectMng(m_pObjectMng);

	PlayerInit();
	Gimmick_ManagerInit();
	TitleInit();

	BlockTwoLoopInit();
	//TutorialInit();
	BackgroundInit();
	CameraManager_Initialize();
	//UI
	UI_Init();
	//Result
	ResultInit();

	//���̐���
	pPillar = new CPillar(k_kobeni, Float2(810.0f, 577.5f), Float2(55.0f, 107.5f));
	pActivePillar = new CActivePillar(RectC2D(Float2(700.0f, 235.0f), Float2(50.0f, 215.0f)));
	pActiveOwl = new CActiveOwl(Float2(700.0f, 715.0f), Float2(35.0f, 35.0f), k_kobeni, 60);

	Door_Init(k_kobeni);
}
//=====================================================================//
//                                                                     //
//							�Q�[���̏I������						   //
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
	BlockTwoLoopUnit();

	Door_Uninit();
}

//=====================================================================//
//                                                                     //
//							�Q�[���̍X�V����						   //
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
		BlockTwoLoopUpdate();

		//�I�u�W�F�N�g�̍X�V
		m_pObjectMng->Update();

		//UI Maneger
		UI_Update();

		//pPillar->Update();
		Door_Update();

		//*****************************************************************TEST*****************************************************************************************
		SetRange(GetCaneraRange());
		//*****************************************************************TEST*****************************************************************************************

		//�I�_
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

		break;
	case k_GAME_OVER:

		break;
	default:
		break;
	}
}
//=====================================================================//
//                                                                     //
//							�Q�[���̕`�揈��						   //
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
		Gimmick_ManagerDraw();

		BlockTwoLoopDraw();

		Door_Draw();

		//�I�u�W�F�N�g�̕`��
		m_pObjectMng->Draw();

		//UI�`��
		UI_Draw();

		//PlayerDraw();
		
		//pPillar->Draw();
		break;
	case k_GAME_START:
		PlayerDraw();
		break;
	case k_GAME_FADEOUT:

		break;
	case k_GAME_RESULT:
		ResultUpdate(112);
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
//					 �Z�b�g���݃Q�[���i�s�X�e�[�W					   //
//                                                                     //
//=====================================================================//
void SetGameStage(k_GAME_STAGE gameStage)
{
	g_kGameStage = gameStage;
}
//=====================================================================//
//                                                                     //
//							 �Z�b�g�X�^�[�g�L�[						   //
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
//							�Q�[���I�[�o�[�̏���				       //
//                                                                     //
//=====================================================================//
bool GameOverCheck(void)
{
	return false;
}