//=============================================================================
//
// プレイヤーの生命力UIクラス [UI_PlayerLife.h]
//										Autor:ロ
//										Date:2018/10/18
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "UI_PlayerLife.h"
#include "Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LIFE_POS_X	(35.0f)
//生命力の最大値,初期値
#define PLAYER_LIFE_MAX (3)
//生命力UIの行間
#define LIFE_SPACE (20.0f)

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
UI_PlayerLife::UI_PlayerLife()
{
	//位置の設定
	pos.p.x = LIFE_POS_X;

	//プレイヤー生命力UIの高さを計算する
	pos.p.y = (TextrueGetHeight(k_tutorialMap) - (TextrueGetHeight(k_playerLife) * PLAYER_LIFE_MAX + LIFE_SPACE * (PLAYER_LIFE_MAX - 1)))/2;
	LifeHeight = TextrueGetHeight(k_playerLife);

	//サイズの設定
	pos.hl.x = TextrueGetWidth(k_playerLife) / 2;
	pos.hl.y = LifeHeight / 2;

	//初期化
	//（XY座標,長さ,高さ）を設定
	Sprite::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y), pos.hl.x, pos.hl.y);
	// 画像分割数
	Sprite::SetDivide(1, 1);
	// 現在UV座標設定
	Sprite::SetUVNum(0, 0);
	
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
UI_PlayerLife::~UI_PlayerLife()
{

}

//*****************************************************************************
// 更新
//*****************************************************************************
void UI_PlayerLife::Update() {

}

//*****************************************************************************
// 描画
//*****************************************************************************
void UI_PlayerLife::Draw()
{
	//描画
	LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();

	//背景
	Sprite::SetPos(D3DXVECTOR2(0, 0), TextrueGetWidth(k_playerLifeBG), TextrueGetHeight(k_playerLifeBG));
	Sprite::Draw(pDevice, DirectX3DGetTEXTURE(k_playerLifeBG));

	for (int i = 0;i < PLAYER_LIFE_MAX;i++) {
		Sprite::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y + (LifeHeight + LIFE_SPACE) * i), pos.hl.x, pos.hl.y);
		Sprite::Draw(pDevice, DirectX3DGetTEXTURE(k_playerLife));
	}
}