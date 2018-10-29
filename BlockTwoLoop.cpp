//=====================================================================//
//		ブロック２ループ用処理 [BlockTwoLoop.cpp]                      //
//                                                                     //
//                                               GP52A275 SoSei        //
//                                               2018/10/28            //
//---------------------------------------------------------------------//
//   2018/10/28　                                                      //
//   メインループ用		**空気壁処理未完成							　 //
//                                                                     //
//                                                                     //
//=====================================================================//
#include "BlockTwoLoop.h"
#include "PlayerManager.h"
#include "CBlockTwoObj.h"


#define LOOP_START_POINT_X	(800)		// ブロック２開始ポイント
#define LOOP_END_POINT_X	(1600)		// ブロック２終了ポイント
#define BLOCK_2_AIR_WALL	(1000.0f)	// ブロック２　橋前の空気壁

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
	if (GetPlayerPos(PLAYER_TWO).x < LOOP_START_POINT_X
		|| GetPlayerPos(PLAYER_TWO).x > LOOP_END_POINT_X)
	{
		return;
	}
	//　プレイヤー１は橋を渡れるか
	if (!TrueIsBlockTwoObjOver())
	{
		if (GetPlayerPos(PLAYER_ONE).x > BLOCK_2_AIR_WALL)
		{
			//SetPlayerPos(PLAYER_TWO)   BLOCK_2_AIR_WALL
		}
	}

	//	オブジェ更新
	BlockTwoObjUpdate();

}
