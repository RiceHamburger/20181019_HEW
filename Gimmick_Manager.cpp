//=============================================================================
//
// �M�~�b�N�}�l�[�W���[ [Gimmick_Manager.cpp]
//										Autor:��
//										Date:2018/10/26
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "DirectX3D.h"
#include "Gimmick_Manager.h"
#include "PlayerManager.h"
#include "Gimmick.h"

#define LADDER_HEIGHT_PLUS	(100.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static Gimmick *p_ladder;

//*****************************************************************************
// �M�~�b�N�̏�������
//*****************************************************************************
void Gimmick_ManagerInit(void) {

	p_ladder = new Gimmick(k_ladder, Float2(1761.0f, 236.0f), Float2(37.5f, 215.0f));
}

//*****************************************************************************
// �M�~�b�N�̏I������
//*****************************************************************************
void Gimmick_ManagerUnit(void) {
	delete p_ladder;
}

//*****************************************************************************
// �M�~�b�N�̃A�b�v�f�[�g
//*****************************************************************************
void Gimmick_ManagerUpdate(void) {
	if (Ladder_CollisionCheck(GetPlayerPos(PLAYER_ONE))) {
		SetPlayerClimb(PLAYER_ONE, true);
	}
	else {
		SetPlayerClimb(PLAYER_ONE, false);
	}

	if (Ladder_CollisionCheck(GetPlayerPos(PLAYER_TWO))) {
		SetPlayerClimb(PLAYER_TWO, true);
	}
	else {
		SetPlayerClimb(PLAYER_TWO, false);
	}
}

//*****************************************************************************
// �M�~�b�N�̕`�揈��
//*****************************************************************************
void Gimmick_ManagerDraw(void) {
	
}

bool Ladder_CollisionCheck(D3DXVECTOR2 playerPos) {
	if (playerPos.x >= p_ladder->GetPosition().p.x - p_ladder->GetPosition().hl.x && playerPos.x <= p_ladder->GetPosition().p.x + p_ladder->GetPosition().hl.x) {
		if (playerPos.y >= p_ladder->GetPosition().p.y - p_ladder->GetPosition().hl.y && playerPos.y <= p_ladder->GetPosition().p.y + p_ladder->GetPosition().hl.y + LADDER_HEIGHT_PLUS) {
			return true;
		}
	}
	return false;
}