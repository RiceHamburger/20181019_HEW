//=====================================================================//
//		�u���b�N�Q���[�v�p���� [BlockTwoLoop.cpp]                      //
//                                                                     //
//                                               GP52A275 SoSei        //
//                                               2018/10/28            //
//---------------------------------------------------------------------//
//   2018/10/28�@                                                      //
//   ���C�����[�v�p		**��C�Ǐ���������							�@ //
//   2018/10/28�@                                                      //
//   Sprite3D���p���A�p�x�v�Z�̕`�����ꂽ							   //
//   2018/11/01�@                                                      //
//   �u���b�N�Q�̋�C�ǂƊG�̔������ꂽ							   //
//   �v���C���[�}�l�[�W���[��STOP�@X�����                             //
//   �v���C���[CLASS��X��~���邽�߂̊֐������                        //
//   2018/11/04�@                                                      //
//   �X�C�b�`�����A�v���C���[�P��2�K�ɂ��鎞�̒���				   //
//                                                                     //
//                                                                     //
//=====================================================================//
#include "BlockTwoLoop.h"
#include "PlayerManager.h"
#include "CBlockTwoObj.h"

//=====================================================================//
//                                                                     //
//								�萔��`							   //
//                                                                     //
//=====================================================================//
#define LOOP_START_POINT_X	(800)			// �u���b�N�Q�J�n�|�C���g
#define LOOP_END_POINT_X	(1600)			// �u���b�N�Q�I���|�C���g
#define BLOCK_2_AIR_WALL_LEFT	(940.0f)	// �u���b�N�Q�@���O�̋�C��
#define BLOCK_2_AIR_WALL_RIGHT	(1530.0f)	// �u���b�N�Q�@���O�̋�C��
#define BLOCK_2_BGROUND_Y2		(465.0f)	// �u���b�N�Q�@2�K
#define BOOL_RESET(x)		{if(x == true){x = false;}}		// �`�F�b�N���Z�b�g


//=====================================================================//
//                                                                     //
//							�v���g�^�C�v�錾	                       //
//                                                                     //
//=====================================================================//
static bool BlockTwoCollision(void);

//=====================================================================//
//                                                                     //
//							�O���[�o���ϐ��錾	                       //
//                                                                     //
//=====================================================================//
static bool g_bIsSwitchOn = false;

/* --------------------------------
�u���b�N�Q�̏�������
-------------------------------- */
void BlockTwoLoopInit(void)
{
	BlockTwoObjInit();
}
/* --------------------------------
�u���b�N�Q�̏I������
-------------------------------- */
void BlockTwoLoopUnit(void)
{
	BlockTwoObjUnit();
	g_bIsSwitchOn = false;
}
/* --------------------------------
�u���b�N�Q�̕`�揈��
-------------------------------- */
void BlockTwoLoopDraw(void)
{
	BlockTwoObjDraw();
}
/* --------------------------------
�u���b�N�Q�̍X�V����
-------------------------------- */
void BlockTwoLoopUpdate(void)
{
	//�@�u���b�N�Q�ɂ��邩
	if (GetPlayerPos(PLAYER_ONE).x > LOOP_END_POINT_X
		&& GetPlayerPos(PLAYER_TWO).x > LOOP_END_POINT_X)
	{
		return;
	}
	//�@�v���C���[�P�͋���n��邩
	if (!TrueIsBlockTwoObjOver())
	{
		//�@��C��
		if (GetPlayerPos(PLAYER_TWO).x >= BLOCK_2_AIR_WALL_LEFT)
		{
			SetPlayerMoveStop(PLAYER_TWO);
		}
		//�@�v���C���[�Q��2�K�ɍs�����ꍇ
		if (GetPlayerPos(PLAYER_ONE).y >= BLOCK_2_BGROUND_Y2 
			&& GetPlayerPos(PLAYER_ONE).x <= BLOCK_2_AIR_WALL_RIGHT)
		{
			SetPlayerMoveStop(PLAYER_ONE);
		}
	}

	//	�I�u�W�F�X�V
	if (g_bIsSwitchOn && BlockTwoCollision())
	{
		BlockTwoObjUpdate(true);
	}
	BOOL_RESET(g_bIsSwitchOn);
}

/* --------------------------------
�A�N�V�����s�g�A
�G�𐳂������邽�߂̃L�[�`�F�b�N
-------------------------------- */
void BlockTwoSwitch(void)
{
	g_bIsSwitchOn = true;
}

/* --------------------------------
�����蔻��̍X�V����
-------------------------------- */
bool BlockTwoCollision(void)
{
	/* --------------------------------
	�v�Z�p�ϐ�
	-------------------------------- */
	float xTemp, yTemp;
	float xSpriteTemp, ySpriteTemp;
	/* --------------------------------
	�v���C���[�Ɣ��蕨��
	���S�_����
	-------------------------------- */
	xTemp = fabsf(GetPlayerPos(PLAYER_ONE).x - GetBlockTwoPaintPos().pos.x);
	//yTemp = fabsf(GetPlayerPos(PLAYER_ONE).y - GetBlockTwoPaintPos().pos.y);
	/* --------------------------------
	�v���C���[�Ɣ��蕨��
	�|���S���͈͌v�Z
	-------------------------------- */
	xSpriteTemp = fabsf(GetPlayerHW(PLAYER_ONE).width / 2 + GetBlockTwoPaintPos().width / 2);
	//ySpriteTemp = fabsf(GetPlayerHW(PLAYER_ONE).height / 2 + GetBlockTwoPaintPos().height / 2);
	/* --------------------------------
	�����蔻��
	-------------------------------- */
	if (xTemp <= xSpriteTemp && GetPlayerPos(PLAYER_ONE).y == 35.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

