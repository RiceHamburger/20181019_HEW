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
//#include "Gimmick.h"

#define LADDER_HEIGHT_PLUS	(80.0f)
#define BLOCK_MAX			(3)
#define PLAYER_WIDTH		(25.0f)
#define PLAYER_HEIGHT		(50.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//static Gimmick *p_ladder;
static Gimmick *p_Block[BLOCK_MAX];

//*****************************************************************************
// ギミックの初期処理
//*****************************************************************************
void Gimmick_ManagerInit(void) {

	p_Block[0] = new Gimmick(k_ladder, Float2(1761.0f, 236.0f), Float2(37.5f, 215.0f));
	
	int count = 0;
	for (int i = 1;i < BLOCK_MAX;i++) {
		p_Block[i] = new Gimmick(k_title, Float2(2217.0f, 128.0f + 600.0f * count), Float2(55.0f, 107.0f + 65.0f * count));
		count++;
	}
}

//*****************************************************************************
// ギミックの終了処理
//*****************************************************************************
void Gimmick_ManagerUnit(void) {
	/*delete p_ladder;
	p_ladder = NULL;*/

	for (int i = 0;i < BLOCK_MAX;i++) {
		delete p_Block[i];
		p_Block[i] = NULL;
	}
}

//*****************************************************************************
// ギミックのアップデート
//*****************************************************************************
void Gimmick_ManagerUpdate(void) {
	//はしこの当たり判定
	if (Ladder_CollisionCheck(GetPlayerPos(PLAYER_ONE), p_Block[0])) {
		SetPlayerClimb(PLAYER_ONE, true);
	}
	else {
		SetPlayerClimb(PLAYER_ONE, false);
	}

	if (Ladder_CollisionCheck(GetPlayerPos(PLAYER_TWO), p_Block[0])) {
		SetPlayerClimb(PLAYER_TWO, true);
	}
	else {
		SetPlayerClimb(PLAYER_TWO, false);
	}

	//何も触ていない場合は柱FALSE 
	SetPlayerOnHashira(PLAYER_TWO, false);

	//下
	if (GetPlayerPos(PLAYER_ONE).x >= p_Block[2]->GetPosition().p.x - p_Block[2]->GetPosition().hl.x + 1.0f && GetPlayerPos(PLAYER_ONE).x <= p_Block[2]->GetPosition().p.x + p_Block[2]->GetPosition().hl.x - 1.0f) {
	 	SetPlayerSquats(true);
	}

	//柱の当たり判定
	for (int playerIndex = 0;playerIndex < 2;playerIndex++) {
		for (int j = 1;j < BLOCK_MAX;j++) {
			if (Pillar_CollisionCheck(GetPlayerPos(playerIndex), p_Block[j])) {

				float PlayerLeft = GetPlayerPos(playerIndex).x - PLAYER_WIDTH;
				float PlayerRight = GetPlayerPos(playerIndex).x + PLAYER_WIDTH;
				float PlayerTop = GetPlayerPos(playerIndex).y + PLAYER_HEIGHT;
				float PlayerBottom = GetPlayerPos(playerIndex).y - PLAYER_HEIGHT;

				float hashiraLeft = p_Block[j]->GetPosition().p.x - p_Block[j]->GetPosition().hl.x;
				float hashiraRight = p_Block[j]->GetPosition().p.x + p_Block[j]->GetPosition().hl.x;
				float hashiraTop = p_Block[j]->GetPosition().p.y + p_Block[j]->GetPosition().hl.y;
				float hashiraBottom = p_Block[j]->GetPosition().p.y - p_Block[j]->GetPosition().hl.y;

				//上
				if (PlayerTop > hashiraTop && GetPlayerPos(playerIndex).y > hashiraTop) {
					SetPlayerPosY(playerIndex, hashiraTop + PLAYER_HEIGHT);
					SetPlayerOnHashira(playerIndex, true);
					break;
				}

				//左
				if (PlayerRight > hashiraLeft && GetPlayerPos(playerIndex).x < p_Block[j]->GetPosition().p.x) {
					SetPlayerPosX(playerIndex, hashiraLeft - PLAYER_WIDTH);
				}
				//右
				if (PlayerLeft < hashiraRight && GetPlayerPos(playerIndex).x > p_Block[j]->GetPosition().p.x) {
					SetPlayerPosX(playerIndex, hashiraRight + PLAYER_WIDTH);
				}
				
			}
		}
	}
}

//*****************************************************************************
// ギミックの描画処理
//*****************************************************************************
void Gimmick_ManagerDraw(void) {
	
}

//*****************************************************************************
// 当たり判定処理
//*****************************************************************************
bool Ladder_CollisionCheck(D3DXVECTOR2 playerPos, Gimmick *obstacle) {
	if (playerPos.x >= obstacle->GetPosition().p.x - obstacle->GetPosition().hl.x && playerPos.x <= obstacle->GetPosition().p.x + obstacle->GetPosition().hl.x) {
		if (playerPos.y >= obstacle->GetPosition().p.y - obstacle->GetPosition().hl.y && playerPos.y <= obstacle->GetPosition().p.y + obstacle->GetPosition().hl.y + LADDER_HEIGHT_PLUS) {
			return true;
		}
	}
	return false;
}

bool Pillar_CollisionCheck(D3DXVECTOR2 playerPos, Gimmick *obstacle) {
	float playerLeft = playerPos.x - PLAYER_WIDTH;
	float playerTop = playerPos.y + PLAYER_HEIGHT;
	float playerRight = playerPos.x + PLAYER_WIDTH;
	float playerBottom = playerPos.y - PLAYER_HEIGHT;

	if (playerLeft < obstacle->GetPosition().p.x + obstacle->GetPosition().hl.x && playerRight > obstacle->GetPosition().p.x - obstacle->GetPosition().hl.x) {
		if (playerTop > obstacle->GetPosition().p.y - obstacle->GetPosition().hl.y && playerBottom < obstacle->GetPosition().p.y + obstacle->GetPosition().hl.y) {
			return true;
		}
	}
	return false;
}