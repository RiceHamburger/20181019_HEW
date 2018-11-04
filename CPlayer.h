/*====================================================================================

	プレイヤークラス　 [CPlayer.h]
																Autor	: 西口
																Date	: 2018/09/25
--------------------------------------------------------------------------------------
コメント:
--------------------------------------------------------------------------------------
修正日時:
====================================================================================*/


#ifndef CPLAYER_H
#define CPLAYER_H
/*--------------------------------------------------------------------------------------
	インクルードファイル
--------------------------------------------------------------------------------------*/
#include "CGameObject.h"
#include "Primitive2D.h"
/*--------------------------------------------------------------------------------------
	列挙型 : 構造体
--------------------------------------------------------------------------------------*/
//プレイヤー数
enum {
	ONE,
	TWO,
};


/*--------------------------------------------------------------------------------------
	マクロ定義
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	クラス宣言
--------------------------------------------------------------------------------------*/

/*-------------------------------------------
	プレイヤークラス
-------------------------------------------*/
class CPlayer : public CGameObject
{

private:


	//
	//	メンバ変数
	//
	//ジャンプ判定
	bool m_bJump;

	//しゃがみ
	bool m_Squats;

	//階段判定
	bool m_Climb;

	//プレイヤー数
	int m_numPlayer;

	//柱を触ているかの判定
	bool m_hashiraue;

	static float axis_max;
	static float axis_min;

	//今の床の座標
	int m_Ground;

public:
	
	//
	//	メンバメソッド
	//

	//コンストラクタ : デフォルト
	CPlayer(int num);

	//アップデート
	virtual bool Update(void);

	//描画
	virtual void Draw(void);

	//横移動 : (false 左 : true 右)
	void SetVelocityX(bool direction = true);
	void SetVelocityY(bool direction = true);
	//ジャンプ
	void Jump(void);

	//入力
	void Input(void);

	//*****************************************************************************
	// 移動できる範囲をとる
	//*****************************************************************************
	void SetMoveRange(RECT view_range);

	//*****************************************************************************
	// 階段を登る設定
	//*****************************************************************************
	void SetClimb(bool climbing);

	//*****************************************************************************
	// 登るのFLAGを取る
	//*****************************************************************************
	bool GetClimb(void);

	//*****************************************************************************
	// しゃがみ
	//*****************************************************************************
	void Squats(void);

	//*****************************************************************************
	// しゃがみ設定
	//*****************************************************************************
	void SetSquats(bool sw);

	//*****************************************************************************
	// 位置設定
	//*****************************************************************************
	void SetPosX(float position);
	void SetPosY(float position);

	//*****************************************************************************
	// 柱を触ているかの判定
	//*****************************************************************************
	void SetHashira(bool sw);
};

#endif //_H
