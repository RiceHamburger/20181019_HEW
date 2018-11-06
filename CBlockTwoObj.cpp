//=====================================================================//
//		ブロック２オブジェクラス [CBlockTwoObj.cpp]                    //
//                                                                     //
//                                               GP52A275 SoSei        //
//                                               2018/10/28            //
//---------------------------------------------------------------------//
//   2018/10/28　                                                      //
//   Sprite3Dを継承、角度計算の描画を入れた							   //
//   2018/11/01　                                                      //
//   ブロック２の空気壁と絵の判定を入れた							   //
//   プレイヤーマネージャーにSTOP　Xを入れ                             //
//   プレイヤーCLASSにX停止するための関数を入れ                        //
//   2018/11/04　                                                      //
//   スイッチを入れ、プレイヤー１が2階にいる時の調整				   //
//                                                                     //
//                                                                     //
//=====================================================================//
#include "CBlockTwoObj.h"
#include "Config.h"

//=====================================================================//
//                                                                     //
//								定数定義							   //
//                                                                     //
//=====================================================================//
#define ROTATE_ZERO	(0)			//　角度０
#define ROTATE_INIT	(60.0f)		//　初期の角度
#define ROTATE_MOVE_VALUE	(0.25f)		//　角度移動の量
#define ROTATE_OBJ_Y_MOVE_VALUE (0.5f)	//　オブジェ移動の量
#define ROTATE_OBJ_X_MOVE_VALUE (0.35f)	//　オブジェ移動の量
#define ROTATE_G	(1.25f)	//　オブジェ移動の減衰

//=====================================================================//
//                                                                     //
//							グローバル変数宣言	                       //
//                                                                     //
//=====================================================================//
CBlockTwoObj* g_pPaint = NULL;	//　絵のポインター
CBlockTwoObj* g_pBridge = NULL;	//　橋のポインター

float g_rotate = ROTATE_INIT;	//　共有角度
float g_BridgeYMove = ROTATE_ZERO;	//　橋移動量
float g_BridgeXMove = ROTATE_ZERO;	//　橋移動量


/* --------------------------------
ブロック２オブジェの初期処理
-------------------------------- */
void BlockTwoObjInit(void)
{
	g_pPaint = new CBlockTwoObj(E_PAINT);
	g_pBridge = new CBlockTwoObj(E_BRIDGE);
}			  
/* --------------------------------
ブロック２オブジェの終了処理
-------------------------------- */
void BlockTwoObjUnit(void)
{
	PTR_DELETE(g_pPaint);
	PTR_DELETE(g_pBridge);
}
/* --------------------------------
ブロック２オブジェの描画処理
-------------------------------- */
void BlockTwoObjDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();

	// 絵と橋を描画
	g_pPaint->DrawRotate(pDevice, DirectX3DGetTEXTURE(k_title), D3DXToRadian(g_rotate));
	g_pBridge->DrawRotate(pDevice, DirectX3DGetTEXTURE(k_title), D3DXToRadian(g_rotate));
}

/* --------------------------------
ブロック２オブジェの更新処理
trueの時　角度1回回転する
-------------------------------- */
void BlockTwoObjUpdate(bool bIsRotateUp)
{
	if (bIsRotateUp)
	{
		// 正向きになっているか
		if (g_rotate > ROTATE_ZERO)
		{
			//　回転計算
			g_rotate -= ROTATE_MOVE_VALUE;
			g_BridgeYMove -= ROTATE_OBJ_Y_MOVE_VALUE;
			g_BridgeXMove += ROTATE_OBJ_X_MOVE_VALUE;
			// XY移動のリセット　サイズそのまま
			g_pBridge->SetPos(D3DXVECTOR2(1150.0f + g_BridgeXMove, 620.0f + g_BridgeYMove * ROTATE_G), 220, 20);
		}
		// 正向きを固定
		else if (g_rotate <= ROTATE_ZERO)
		{
			g_rotate = ROTATE_ZERO;
		}
	}
}

/* --------------------------------
ブロック２通過可能か
-------------------------------- */
bool TrueIsBlockTwoObjOver(void)
{
	if (g_rotate == ROTATE_ZERO)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/* --------------------------------
ゲットブロック２絵の中心位置
-------------------------------- */
S_3DVec GetBlockTwoPaintPos(void)
{
	return g_pPaint->GetPos();
}

/* --------------------------------
ブロック２オブジェのクラス
-------------------------------- */
CBlockTwoObj::CBlockTwoObj(E_BlockTwoObj objEnum) 
	: E_ObjType(objEnum)
{
	switch (E_ObjType)
	{
	case E_PAINT:
		SetPos(D3DXVECTOR2(1350.0f, 225.0f), 100, 100);
		SetDivide(1, 1);
		SetUVNum(0, 0);
		break;
	case E_BRIDGE:
		SetPos(D3DXVECTOR2(1150.0f, 620.0f), 220, 20);
		SetDivide(1, 1);
		SetUVNum(0, 0);
		break;
	}
}
CBlockTwoObj::~CBlockTwoObj(){}