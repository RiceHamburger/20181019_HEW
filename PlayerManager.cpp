#include "PlayerManager.h"
#include "CPlayer.h"



static CPlayer* g_pPlayer1 = NULL;		// プレイヤー１
static CPlayer* g_pPlayer2 = NULL;		// プレイヤー2

/* --------------------------------
プレイヤーの初期処理
-------------------------------- */
void PlayerInit(void)
{
	g_pPlayer1 = new CPlayer(ONE);
	g_pPlayer2 = new CPlayer(TWO);
}
/* --------------------------------
プレイヤーの終了処理
-------------------------------- */
void PlayerUnit(void)
{
	delete g_pPlayer1;
	g_pPlayer1 = NULL;
	delete g_pPlayer2;
	g_pPlayer2 = NULL;
}
/* --------------------------------
プレイヤーの描画処理
-------------------------------- */
void PlayerDraw(void)
{
	g_pPlayer1->Draw();
	g_pPlayer2->Draw();
}
/* --------------------------------
プレイヤーの更新処理
-------------------------------- */
void PlayerUpdate(void)
{
	g_pPlayer1->Update();
	g_pPlayer2->Update();
}
/* --------------------------------
セットプレイヤーの移動
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
セットプレイヤーの移動(上下)
-------------------------------- */
void SetPlayerMoveY(int index, bool bIs)
{
	switch (index) {
	case PLAYER_ONE:
		g_pPlayer1->SetVelocityY(bIs);
		break;

	case PLAYER_TWO:
		g_pPlayer2->SetVelocityY(bIs);
		break;

	}
}
/* --------------------------------
セットプレイヤーのジャンプ
-------------------------------- */
void SetPlayerJump(int index)
{
	switch (index) {
	case PLAYER_ONE:
		//11/1　しゃがみに変更
		g_pPlayer1->Squats();
		break;

	case PLAYER_TWO:
		g_pPlayer2->Jump();
		break;

	}

}
/* --------------------------------
ゲットプレイヤーの座標
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
// 移動できる範囲をとる
//*****************************************************************************
void SetRange(RECT view_range) {
	g_pPlayer1->SetMoveRange(view_range);
}

//*****************************************************************************
// 階段を登るの設定
//*****************************************************************************
void SetPlayerClimb(int index, bool bIs) {
	switch (index) {
	case PLAYER_ONE:
		return g_pPlayer1->SetClimb(bIs);
		break;

	case PLAYER_TWO:
		return g_pPlayer2->SetClimb(bIs);
		break;

	}
}

//*****************************************************************************
// 登るのFLAG
//*****************************************************************************
bool GetPlayerClimb(int index) {
	switch (index) {
	case PLAYER_ONE:
		return g_pPlayer1->GetClimb();
		break;

	case PLAYER_TWO:
		return g_pPlayer2->GetClimb();
		break;

	}
}

//*****************************************************************************
// 位置設定X
//*****************************************************************************
void SetPlayerPosX(int index, float newPosition) {
	switch (index) {
	case PLAYER_ONE:
		g_pPlayer1->SetPosX(newPosition);
		break;

	case PLAYER_TWO:
		g_pPlayer2->SetPosX(newPosition);
		break;

	}
}
//*****************************************************************************
// 位置設定Y
//*****************************************************************************
void SetPlayerPosY(int index, float newPosition) {
	switch (index) {
	case PLAYER_ONE:
		g_pPlayer1->SetPosY(newPosition);
		break;

	case PLAYER_TWO:
		g_pPlayer2->SetPosY(newPosition);
		break;

	}
}
//*****************************************************************************
// 柱を触ているかの判定
//*****************************************************************************
void SetPlayerOnHashira(int index, bool bIs) {
	switch (index) {
	case PLAYER_TWO:
		return g_pPlayer2->SetHashira(bIs);
		break;

	}
}

//*****************************************************************************
// しゃがみ設定
//*****************************************************************************
void SetPlayerSquats(bool sw) {
	g_pPlayer1->SetSquats(sw);
}