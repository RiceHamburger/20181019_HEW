//=====================================================================//
//		ブロック２ループ用処理 [BlockTwoLoop.cpp]                      //
//                                                                     //
//                                               GP52A275 SoSei        //
//                                               2018/10/28            //
//---------------------------------------------------------------------//
//   2018/10/28　                                                      //
//   メインループ用		**空気壁処理未完成							　 //
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
#include "BlockTwoLoop.h"
#include "PlayerManager.h"
#include "CBlockTwoObj.h"

//=====================================================================//
//                                                                     //
//								定数定義							   //
//                                                                     //
//=====================================================================//
#define LOOP_START_POINT_X	(800)			// ブロック２開始ポイント
#define LOOP_END_POINT_X	(1600)			// ブロック２終了ポイント
#define BLOCK_2_AIR_WALL_LEFT	(940.0f)	// ブロック２　橋前の空気壁
#define BLOCK_2_AIR_WALL_RIGHT	(1530.0f)	// ブロック２　橋前の空気壁
#define BLOCK_2_BGROUND_Y2		(465.0f)	// ブロック２　2階
#define BOOL_RESET(x)		{if(x == true){x = false;}}		// チェックリセット


//=====================================================================//
//                                                                     //
//							プロトタイプ宣言	                       //
//                                                                     //
//=====================================================================//
static bool BlockTwoCollision(void);

//=====================================================================//
//                                                                     //
//							グローバル変数宣言	                       //
//                                                                     //
//=====================================================================//
static bool g_bIsSwitchOn = false;

/* --------------------------------
ブロック２の初期処理
-------------------------------- */
void BlockTwoLoopInit(void)
{
	BlockTwoObjInit();
}
/* --------------------------------
ブロック２の終了処理
-------------------------------- */
void BlockTwoLoopUnit(void)
{
	BlockTwoObjUnit();
	g_bIsSwitchOn = false;
}
/* --------------------------------
ブロック２の描画処理
-------------------------------- */
void BlockTwoLoopDraw(void)
{
	BlockTwoObjDraw();
}
/* --------------------------------
ブロック２の更新処理
-------------------------------- */
void BlockTwoLoopUpdate(void)
{
	//　ブロック２にいるか
	if (GetPlayerPos(PLAYER_ONE).x > LOOP_END_POINT_X
		&& GetPlayerPos(PLAYER_TWO).x > LOOP_END_POINT_X)
	{
		return;
	}
	//　プレイヤー１は橋を渡れるか
	if (!TrueIsBlockTwoObjOver())
	{
		//　空気壁
		if (GetPlayerPos(PLAYER_TWO).x >= BLOCK_2_AIR_WALL_LEFT)
		{
			SetPlayerMoveStop(PLAYER_TWO);
		}
		//　プレイヤー２が2階に行った場合
		if (GetPlayerPos(PLAYER_ONE).y >= BLOCK_2_BGROUND_Y2 
			&& GetPlayerPos(PLAYER_ONE).x <= BLOCK_2_AIR_WALL_RIGHT)
		{
			SetPlayerMoveStop(PLAYER_ONE);
		}
	}

	//	オブジェ更新
	if (g_bIsSwitchOn && BlockTwoCollision())
	{
		BlockTwoObjUpdate(true);
	}
	BOOL_RESET(g_bIsSwitchOn);
}

/* --------------------------------
アクション行使、
絵を正しくするためのキーチェック
-------------------------------- */
void BlockTwoSwitch(void)
{
	g_bIsSwitchOn = true;
}

/* --------------------------------
当たり判定の更新処理
-------------------------------- */
bool BlockTwoCollision(void)
{
	/* --------------------------------
	計算用変数
	-------------------------------- */
	float xTemp, yTemp;
	float xSpriteTemp, ySpriteTemp;
	/* --------------------------------
	プレイヤーと判定物の
	中心点距離
	-------------------------------- */
	xTemp = fabsf(GetPlayerPos(PLAYER_ONE).x - GetBlockTwoPaintPos().pos.x);
	//yTemp = fabsf(GetPlayerPos(PLAYER_ONE).y - GetBlockTwoPaintPos().pos.y);
	/* --------------------------------
	プレイヤーと判定物の
	ポリゴン範囲計算
	-------------------------------- */
	xSpriteTemp = fabsf(GetPlayerHW(PLAYER_ONE).width / 2 + GetBlockTwoPaintPos().width / 2);
	//ySpriteTemp = fabsf(GetPlayerHW(PLAYER_ONE).height / 2 + GetBlockTwoPaintPos().height / 2);
	/* --------------------------------
	当たり判定
	-------------------------------- */
	if (xTemp <= xSpriteTemp && GetPlayerPos(PLAYER_ONE).y == 35.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

