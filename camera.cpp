//=============================================================================
//
// カメラクラス [camera.cpp]
//										Autor:ロ
//										Date:2018/09/30
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "DirectX3D.h"
#include "camera.h"
#include "input.h"

//player life UI size
#include "Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH		(1600)
#define SCREEN_HEIGHT		(900)
#define X_AXIS_MAX			(3200.0f)

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Camera::Camera()
{
	pos = { 0,450.0f };
	D3DXMatrixOrthoLH(&orthographicMatrix, SCREEN_WIDTH, SCREEN_HEIGHT, -100.0f, 100.0f);
	D3DXMatrixIdentity(&identityMatrix);

	view_range = { 0,SCREEN_HEIGHT,SCREEN_WIDTH,0 };

	UI_Width = TextrueGetWidth(k_playerLifeBG);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Camera::~Camera()
{

}

//*****************************************************************************
// アップデート
//*****************************************************************************
void Camera::Update(D3DXVECTOR2 player1_vec, D3DXVECTOR2 player2_vec)
{
	//follow player
	float viewCenter = (player1_vec.x + player2_vec.x - UI_Width) / 2;
	pos.x = viewCenter;

	pos.x = max(0 + SCREEN_WIDTH/2, pos.x);
	pos.x = min(pos.x, X_AXIS_MAX - SCREEN_WIDTH / 2);

	viewMatrix = D3DXMATRIX(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-pos.x, -pos.y, 0, 1
	);

	//view range update
	view_range.left = pos.x - SCREEN_WIDTH / 2 + UI_Width;
	view_range.top = pos.x + SCREEN_HEIGHT / 2;
	view_range.right = pos.x + SCREEN_WIDTH / 2;
	view_range.bottom = pos.x - SCREEN_HEIGHT / 2;
}

//*****************************************************************************
// トランスフォーム関連ステートを設定する
//*****************************************************************************
void Camera::SetTransform()
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = DirectX3DGetDevice();
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
}

//*****************************************************************************
// カメラの範囲
//*****************************************************************************
RECT Camera::GetViewRange() {
	return view_range;
}