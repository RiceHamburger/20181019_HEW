//=============================================================================
//
// ギミックマネージャー [Gimmick_Manager.cpp]
//										Autor:ロ
//										Date:2018/10/26
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "DirectX3D.h"
#include "Gimmick_Manager.h"
#include "PlayerManager.h"
#include "Gimmick.h"

#define LADDER_HEIGHT_PLUS	(100.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static Gimmick *p_ladder;

//*****************************************************************************
// ギミックの初期処理
//*****************************************************************************
void Gimmick_ManagerInit(void) {

	p_ladder = new Gimmick(k_ladder, Float2(1761.0f, 236.0f), Float2(37.5f, 215.0f));
}

//*****************************************************************************
// ギミックの終了処理
//*****************************************************************************
void Gimmick_ManagerUnit(void) {
	delete p_ladder;
}

//*****************************************************************************
// ギミックのアップデート
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
// ギミックの描画処理
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