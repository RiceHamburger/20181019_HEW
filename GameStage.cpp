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
	TitleInit();
	//TutorialInit();
	BackgroundInit();
	CameraManager_Initialize();
	//UI
	UI_Init();
	Gimmick_ManagerInit();

	//���̐���
	pPillar = new CPillar(k_kobeni, Float2(810.0f, 577.5f), Float2(55.0f, 107.5f));
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

		//�I�u�W�F�N�g�̍X�V
		m_pObjectMng->Update();

		//UI Maneger
		UI_Update();

		//pPillar->Update();

		//*****************************************************************TEST*****************************************************************************************
		SetRange(GetCaneraRange());
		//*****************************************************************TEST*****************************************************************************************

		//�I�_
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

		//�I�u�W�F�N�g�̕`��
		m_pObjectMng->Draw();

		//UI�`��
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