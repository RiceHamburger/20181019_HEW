//=====================================================================//
//		�u���b�N�Q���[�v�p���� [BlockTwoLoop.cpp]                      //
//                                                                     //
//                                               GP52A275 SoSei        //
//                                               2018/10/28            //
//---------------------------------------------------------------------//
//   2018/10/28�@                                                      //
//   ���C�����[�v�p		**��C�Ǐ���������							�@ //
//                                                                     //
//                                                                     //
//=====================================================================//
#include "BlockTwoLoop.h"
#include "PlayerManager.h"
#include "CBlockTwoObj.h"


#define LOOP_START_POINT_X	(800)		// �u���b�N�Q�J�n�|�C���g
#define LOOP_END_POINT_X	(1600)		// �u���b�N�Q�I���|�C���g
#define BLOCK_2_AIR_WALL	(1000.0f)	// �u���b�N�Q�@���O�̋�C��

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
	if (GetPlayerPos(PLAYER_TWO).x < LOOP_START_POINT_X
		|| GetPlayerPos(PLAYER_TWO).x > LOOP_END_POINT_X)
	{
		return;
	}
	//�@�v���C���[�P�͋���n��邩
	if (!TrueIsBlockTwoObjOver())
	{
		if (GetPlayerPos(PLAYER_ONE).x > BLOCK_2_AIR_WALL)
		{
			//SetPlayerPos(PLAYER_TWO)   BLOCK_2_AIR_WALL
		}
	}

	//	�I�u�W�F�X�V
	BlockTwoObjUpdate();

}
