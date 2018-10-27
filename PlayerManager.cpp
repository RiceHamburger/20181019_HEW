#include "PlayerManager.h"
#include "CPlayer.h"



static CPlayer* g_pPlayer1 = NULL;		// �v���C���[�P
static CPlayer* g_pPlayer2 = NULL;		// �v���C���[2

/* --------------------------------
�v���C���[�̏�������
-------------------------------- */
void PlayerInit(void)
{
	g_pPlayer1 = new CPlayer(ONE);
	g_pPlayer2 = new CPlayer(TWO);
}
/* --------------------------------
�v���C���[�̏I������
-------------------------------- */
void PlayerUnit(void)
{
	delete g_pPlayer1;
	g_pPlayer1 = NULL;
	delete g_pPlayer2;
	g_pPlayer2 = NULL;
}
/* --------------------------------
�v���C���[�̕`�揈��
-------------------------------- */
void PlayerDraw(void)
{
	g_pPlayer1->Draw();
	g_pPlayer2->Draw();
}
/* --------------------------------
�v���C���[�̍X�V����
-------------------------------- */
void PlayerUpdate(void)
{
	g_pPlayer1->Update();
	g_pPlayer2->Update();
}
/* --------------------------------
�Z�b�g�v���C���[�̈ړ�
-------------------------------- */
void SetPlayerMove(int index , bool bIs)
{
	switch (index) {
	case PLAYER_ONE:
		g_pPlayer1->SetVelocityX(bIs);
		break;

	case PLAYER_TWO:
		g_pPlayer2->SetVelocityX(bIs);
		break;

	}
}
/* --------------------------------
�Z�b�g�v���C���[�̃W�����v
-------------------------------- */
void SetPlayerJump(int index)
{
	switch (index) {
	case PLAYER_ONE:
		g_pPlayer1->Jump();
		break;

	case PLAYER_TWO:
		g_pPlayer2->Jump();
		break;

	}

}
/* --------------------------------
�Q�b�g�v���C���[�̍��W
-------------------------------- */
D3DXVECTOR2 GetPlayerPos(int index)
{
	switch (index) {
	case PLAYER_ONE:
		return g_pPlayer1->GetPos().pos;
		break;

	case PLAYER_TWO:
		return g_pPlayer2->GetPos().pos;
		break;

	}
}

//*****************************************************************************
// �ړ��ł���͈͂��Ƃ�
//*****************************************************************************
void SetRange(RECT view_range) {
	g_pPlayer1->SetMoveRange(view_range);
}