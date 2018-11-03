/*====================================================================================

	プレイヤークラス　 [CPlayer.cpp]
																Autor	: 西口
																Date	: 2018/09/25
--------------------------------------------------------------------------------------
コメント:
--------------------------------------------------------------------------------------
修正日時:
====================================================================================*/


/*--------------------------------------------------------------------------------------
	インクルードファイル
--------------------------------------------------------------------------------------*/
#include "CPlayer.h"
#include "Texture.h"

/*--------------------------------------------------------------------------------------
	列挙型 : 構造体
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	マクロ定義
--------------------------------------------------------------------------------------*/

//#define GROUND_Y1					(800.0f)
//#define GROUND_Y2					(400.0f)
//#define GRAVITY						(0.8f)
//#define JUMP_VALUE					(-18.0f)

//*****************************************************************弄ったところ*****************************************************************************************
#define GROUND_Y1					(-15.0f)
#define GROUND_Y2					(465.0f)
#define GRAVITY						(-0.98f)
#define JUMP_VALUE					(20.0f)
#define X_AXIS_MAX					(3840.0f)
#define SQUATA_HEIGHT				(40.0f)
//*****************************************************************弄ったところ*****************************************************************************************

//プレイヤー1
#define INITIALIZE_POS_X			(120.0f)
#define INITIALIZE_POS_Y			(300.0f)
#define PLAYER_WIDTH				(25.0f)
#define PLAYER_HEIGHT				(50.0f)
#define INITIALIZE_VELOCITY_X		(0.0f)
#define INITIALIZE_VELOCITY_Y		(0.0f)
#define VECDIR_X					(0.9f)
#define ACCELERATION				(1.0f)
#define VELOCITY_RESIST				(0.9f)

//プレイヤー2
#define INITIALIZE_POS_X2			(120.0f)
#define INITIALIZE_POS_Y2			(600.0f)


#define SCREEN_WIDTH				(1600)
#define SCREEN_HEIGHT				(900)

/*--------------------------------------------------------------------------------------
	クラス実行部分
--------------------------------------------------------------------------------------*/

/*-------------------------------------------
	プレイヤークラス
-------------------------------------------*/

//
//	メンバメソッド
//
//*****************************************************************弄ったところ*****************************************************************************************
//静的メンバ変数
float CPlayer::axis_max = SCREEN_WIDTH;
float CPlayer::axis_min = 0;
//*****************************************************************弄ったところ*****************************************************************************************

//コンストラクタ : デフォルト
CPlayer::CPlayer(int num) {

	//位置の設定
	switch (num) {
	case ONE:
		m_numPlayer = num;
		pos.p.x = INITIALIZE_POS_X;
		pos.p.y = INITIALIZE_POS_Y;
		break;
		
	case TWO:
		m_numPlayer = num;
		pos.p.x = INITIALIZE_POS_X2;
		pos.p.y = INITIALIZE_POS_Y2;
		break;
	}

	//サイズの設定
	pos.hl.x = PLAYER_WIDTH;
	pos.hl.y = PLAYER_HEIGHT;



	//テクスチャの設定
	//m_textureIndex = ;

	//速度の設定
	m_velocity.x = NULL;
	m_velocity.y = NULL;

	//移動方向の設定
	m_vecDir.x = NULL;

	//重力の設定
	m_vecDir.y = GRAVITY;

	//柱を触ているかの判定
	m_hashiraue = false;

	//初期化
	//Sprite::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y), 64, 64);	// （D3DXVECTOR2(XY座標),長さ,高さ）を設定
	//Sprite::SetDivide(1, 1);									// 画像分割数
	//Sprite::SetUVNum(0, 0);									// 現在UV座標設定

	//*****************************************************************弄ったところ*****************************************************************************************
	Sprite3D::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y), pos.hl.x, pos.hl.y);	// （D3DXVECTOR2(XY座標),長さ,高さ）を設定
	Sprite3D::SetDivide(1, 1);							    // 画像分割数
	Sprite3D::SetUVNum(0, 0);									// 現在UV座標設定
	//*****************************************************************弄ったところ*****************************************************************************************
}




//アップデート
bool CPlayer::Update(void) {


	//移動ベクトルの正規化
	//m_vecDir.norm();

	//速度更新
	m_velocity = m_velocity + m_vecDir * ACCELERATION;

	//位置情報の更新
	pos.p = pos.p + m_velocity;

	switch (m_numPlayer) {
	case ONE:
		//*****************************************************************弄ったところ*****************************************************************************************
		//画面外補正
		//X軸
		/*pos.p.x = max(0 + pos.hl.x, pos.p.x);*/
		//pos.p.x = min(pos.p.x, SCREEN_WIDTH - pos.hl.x);

		//Y軸
		/*pos.p.y = max(0 + pos.hl.y, pos.p.y);
		pos.p.y = min(pos.p.y, GROUND_Y1 - pos.hl.y);*/

		//着地判定
		/*if (pos.p.y >= GROUND_Y1 - pos.hl.y) {
			m_bJump = false;
			m_velocity.y = 0.0f;
		}
		else {
			m_bJump = true;
		}*/

		//X軸
		pos.p.x = max(axis_min + pos.hl.x, pos.p.x);
		pos.p.x = min(pos.p.x, axis_max - pos.hl.x);

		//Y軸
		pos.p.y = max(m_Ground + pos.hl.y, pos.p.y);
		pos.p.y = min(pos.p.y, SCREEN_HEIGHT - pos.hl.y);
		
		

		//着地判定
		/*if (pos.p.y <= m_Ground + pos.hl.y && !m_Climb) {
			m_bJump = false;
			m_velocity.y = 0.0f;
		}
		else {
			m_bJump = true;
		}*/

		if (m_Squats) {
			pos.hl.y = SQUATA_HEIGHT;
		}
		else {
			pos.hl.y = PLAYER_HEIGHT;
		}

		//*****************************************************************弄ったところ*****************************************************************************************

		break;

	case TWO:
		//*****************************************************************弄ったところ*****************************************************************************************
		//画面外補正
		//X軸
		/*pos.p.x = max(0 + pos.hl.x, pos.p.x);
		pos.p.x = min(pos.p.x, SCREEN_WIDTH - pos.hl.x);*/

		//Y軸
		/*pos.p.y = max(0 + pos.hl.y, pos.p.y);
		pos.p.y = min(pos.p.y, GROUND_Y2 - pos.hl.y);*/

		//着地判定
		/*if (pos.p.y >= GROUND_Y2 - pos.hl.y) {
			m_bJump = false;
			m_velocity.y = 0.0f;
		}
		else {
			m_bJump = true;
		}*/

		//X軸
		pos.p.x = max(axis_min + pos.hl.x, pos.p.x);
		pos.p.x = min(pos.p.x, axis_max - pos.hl.x);

		//Y軸
		pos.p.y = max(m_Ground + pos.hl.y, pos.p.y);
		pos.p.y = min(pos.p.y, SCREEN_HEIGHT - pos.hl.y);

		//着地判定
		if (pos.p.y <= m_Ground + pos.hl.y) {
			m_bJump = false;
			m_velocity.y = 0.0f;
		}
		else {
			m_bJump = true;
		}
		//*****************************************************************弄ったところ*****************************************************************************************
		break;
	}

	//減速
	m_velocity.x = m_velocity.x * VELOCITY_RESIST;

	//移動ベクトルの初期化
	m_vecDir.x = NULL;
	
	//しゃがみの初期化
	m_Squats = false;

	//階段判定
	if (m_Climb || m_hashiraue) {
		m_velocity.y = m_velocity.y * VELOCITY_RESIST;
		m_vecDir.y = NULL;
	}
	else {
		m_vecDir.y = GRAVITY;
	}

	if (pos.p.y < GROUND_Y2 || m_Climb) {
		m_Ground = GROUND_Y1;
	}
	else {
		m_Ground = GROUND_Y2;
	}

	return true;
}

//描画
void CPlayer::Draw(void) {

	//プレイヤーの描画
	//ppDrawer->SetTexture(k_kobeni);
	//ppDrawer->Draw(pos.p, pos.hl, D3DCOLOR_RGBA(255, 255, 255, 255));
	
	//*****************************************************************弄ったところ*****************************************************************************************
	////座標初期化
	Sprite3D::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y), pos.hl.x, pos.hl.y);


	////描画
	//LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();
	//Sprite3D::Draw(pDevice, DirectX3DGetTEXTURE(k_kobeni));
	Sprite3D::Draw(k_kobeni , pos , -1.0f);
	//*****************************************************************弄ったところ*****************************************************************************************
}

//横移動 : (false 右 : true 左)
void CPlayer::SetVelocityX(bool direction) {

	if (direction) {
		m_vecDir.x += VECDIR_X;
	}
	else {
		m_vecDir.x -= VECDIR_X;
	}
}

//縦移動 : (false 下 : true 上)
void CPlayer::SetVelocityY(bool direction) {

	if (direction) {
		m_vecDir.y += VECDIR_X;
	}
	else {
		m_vecDir.y -= VECDIR_X;
	}
}

//ジャンプ
void CPlayer::Jump(void) {

	//ジャンプ中でないならジャンプ
	if (!m_bJump) {

		//フラグをジャンプ中に変更
		m_bJump = true;

		//加速度にジャンプ力を設定
		m_velocity.y = JUMP_VALUE;

	}
}


//*****************************************************************************
// 移動できる範囲をとる
//*****************************************************************************
void CPlayer::SetMoveRange(RECT view_range) {
	axis_max = view_range.right;
	axis_min = view_range.left;
}

//*****************************************************************************
// 階段を登る設定
//*****************************************************************************
void CPlayer::SetClimb(bool climbing) {
	m_Climb = climbing;
}

//*****************************************************************************
// 登るのFLAGを取る
//*****************************************************************************
bool CPlayer::GetClimb(void) {
	return m_Climb;
}

//*****************************************************************************
// しゃがみ
//*****************************************************************************
void CPlayer::Squats(void) {
	if (!m_Squats) {
		m_Squats = true;
	}
}

//*****************************************************************************
// 位置設定X
//*****************************************************************************
void CPlayer::SetPosX(float position) {
	pos.p.x = position;
}
//*****************************************************************************
// 位置設定Y
//*****************************************************************************
void CPlayer::SetPosY(float position) {
	pos.p.y = position;
}
//*****************************************************************************
// 柱を触ているかの判定
//*****************************************************************************
void CPlayer::SetHashira(bool sw) {
	m_hashiraue = sw;
}