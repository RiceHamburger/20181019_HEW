/*====================================================================================

門クラス　 [CDoor.cpp]
Autor	: ユ・ビョンチャン
Date	: 2018/10/26
--------------------------------------------------------------------------------------
コメント:
門クラス : 背景

--------------------------------------------------------------------------------------
修正日時:
====================================================================================*/


/*--------------------------------------------------------------------------------------
インクルードファイル
--------------------------------------------------------------------------------------*/
#include "CDoor.h"
#include "PlayerManager.h"
/*--------------------------------------------------------------------------------------
列挙型 : 構造体
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
マクロ定義
--------------------------------------------------------------------------------------*/
#define DOORCOUNT (2)											//ドアー数
#define DOORCOLORTIME (5)										//時間測定基準
#define DOORCOLOR (D3DCOLOR_RGBA(255, 100, 200, 255))			//変える色
#define DOORCOLOR_WHITE (D3DCOLOR_RGBA(255, 255, 255, 255))		//白色
#define DOOR_WIDTH (100)
#define DOOR_HEIGHT (100)

/*--------------------------------------------------------------------------------------
クラス宣言
--------------------------------------------------------------------------------------*/

//テクスチャ、上ドアー位置、下ドアー位置
CDoor::CDoor(k_Texture index, D3DXVECTOR2 pos0, D3DXVECTOR2 pos1)
{
	m_TextureIndex = index;

	m_pos[PLAYER_ONE] = pos0;
	m_pos[PLAYER_TWO] = pos1;
	
	m_color[PLAYER_ONE] = DOORCOLOR;
	m_color[PLAYER_TWO] = DOORCOLOR;

	m_OnOff[PLAYER_ONE] = false;
	m_OnOff[PLAYER_TWO] = false;
	m_OK = false;

	Sprite3D::SetColor(DOORCOLOR_WHITE);
	Sprite3D::SetDivide(1, 1);
	Sprite3D::SetUVNum(0, 0);
}

CDoor::CDoor(k_Texture index)
{
	m_TextureIndex = index;
	
	m_pos[PLAYER_ONE] = D3DXVECTOR2(3015.0f, 120.0f);
	m_pos[PLAYER_TWO] = D3DXVECTOR2(3015.0f, 570.0f);

	m_color[PLAYER_ONE] = DOORCOLOR;
	m_color[PLAYER_TWO] = DOORCOLOR;

	m_OnOff[PLAYER_ONE] = false;
	m_OnOff[PLAYER_TWO] = false;
	m_OK = false;

	Sprite3D::SetColor(DOORCOLOR_WHITE);
	Sprite3D::SetDivide(1, 1);
	Sprite3D::SetUVNum(0, 0);
}

CDoor::~CDoor()
{

}

//ドアーが押されたか判断(中で当り判定やってる)
void CDoor::Switch(int index)
{
	switch (index)
	{
	case PLAYER_TWO:
		//当り判定
		if (GetPlayerPos(PLAYER_TWO).y <= m_pos[PLAYER_ONE].y + DOOR_HEIGHT &&
			GetPlayerPos(PLAYER_TWO).y >= m_pos[PLAYER_ONE].y - DOOR_HEIGHT) {
			if (GetPlayerPos(PLAYER_TWO).x <= m_pos[PLAYER_ONE].x + DOOR_WIDTH &&
				GetPlayerPos(PLAYER_TWO).x >= m_pos[PLAYER_ONE].x - DOOR_WIDTH) {
				//Onになった処理
				m_OnOff[PLAYER_ONE] = true;

				if (m_OnOff[PLAYER_ONE]) {
					if (m_OnOff[PLAYER_TWO]) {
						//両方押されているとここ
						m_OK = true;
					}
				}
			}
			//時間を入れる
			start[PLAYER_ONE] = clock();
			}

		break;

	case PLAYER_ONE:
		//当り判定
		if (GetPlayerPos(PLAYER_ONE).y <= m_pos[PLAYER_TWO].y + DOOR_HEIGHT &&
			GetPlayerPos(PLAYER_ONE).y >= m_pos[PLAYER_TWO].y - DOOR_HEIGHT) {
			if (GetPlayerPos(PLAYER_ONE).x <= m_pos[PLAYER_TWO].x + DOOR_WIDTH &&
				GetPlayerPos(PLAYER_ONE).x >= m_pos[PLAYER_TWO].x - DOOR_WIDTH) {
				//Onになった処理
				m_OnOff[PLAYER_TWO] = true;

				if (m_OnOff[PLAYER_TWO]) {
					if (m_OnOff[PLAYER_ONE]) {
						//両方押されているとここ
						m_OK = true;
					}
				}
			}
			//時間を入れる
			start[PLAYER_TWO] = clock();
		}

		break;

	default:
		break;
	}
}

void CDoor::Draw(void)
{
	for (int i = 0; i < DOORCOUNT; i++) {

		Sprite3D::SetPos(m_pos[i], DOOR_WIDTH, DOOR_HEIGHT);	//ドアーの位置を描く度入れる

		if (m_OnOff[i]) {										//ドアーがオンだったら指定色
			Sprite3D::SetColor(m_color[i]);
		}
		else {													//オフだったら白
			Sprite3D::SetColor(DOORCOLOR_WHITE);
		}

		Sprite3D::Draw(m_TextureIndex);

	}
}

//ドアーが押された時の時間で色変えの時間を決めてる
void CDoor::ColorUpdate(void)
{
	for (int i = 0; i < DOORCOUNT; i++) {
		if (m_OnOff[i]) {
			end[i] = clock();
			if (((end[i] - start[i]) / 1000) >= DOORCOLORTIME) {
				//DOORCOLORTIMEの時間以上になるとオフに戻る
				m_OnOff[i] = false;
			}
		}
	}
}

//両方押されたらtrueになる
bool CDoor::Fin(void)
{
	return m_OK;
}