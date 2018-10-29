/*====================================================================================

	アクティブピラークラス　 [CActivePillar.cpp]
																Autor	: 西口
																Date	: 2018/10/27
--------------------------------------------------------------------------------------
コメント:
--------------------------------------------------------------------------------------
修正日時:
====================================================================================*/


/*--------------------------------------------------------------------------------------
	インクルードファイル
--------------------------------------------------------------------------------------*/
#include "CActivePillar.h"

/*--------------------------------------------------------------------------------------
	列挙型 : 構造体
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	マクロ定義
--------------------------------------------------------------------------------------*/
#define PILLAR_MOVESPEED	(10.0f)
/*--------------------------------------------------------------------------------------
	クラス実行部分
--------------------------------------------------------------------------------------*/

//コンストラクタ : デフォルト
CActivePillar::CActivePillar(RectC2D pos) {

	//二つ分の柱の設定
	//上側
	m_pPillar[0].p = Float2(pos.p.x , pos.p.y + (pos.hl.y / 2));
	m_pPillar[0].hl = pos.hl / 2;
	m_startPos[0] = m_pPillar[0].p;
	m_endPos[0] = Float2(pos.p.x, pos.p.y + (pos.hl.y * 2));
	m_bDir[0] = true;
	//下側
	m_pPillar[1].p = Float2(pos.p.x, pos.p.y - (pos.hl.y / 2));
	m_pPillar[1].hl = pos.hl / 2;
	m_startPos[1] = m_pPillar[1].p;
	m_endPos[1] = Float2(pos.p.x, pos.p.y - (pos.hl.y * 2));
	m_bDir[1] = true;

	Sprite3D::SetDivide(1, 1);							    // 画像分割数
	Sprite3D::SetUVNum(0, 0);									// 現在UV座標設定

	//アクティブフラグをfalseに設定
	m_isActive = true;

}

//アップデート
bool CActivePillar::Update() {

	//アクティブフラグが真であれば動作を行う
	if (m_isActive) {

		MoveTopPillar();

		MoveBottomPillar();
	}

	return true;
}

//描画
void CActivePillar::Draw() {


	Sprite3D::Draw(k_kobeni, m_pPillar[0], 0.0f);
	Sprite3D::Draw(k_kobeni, m_pPillar[1], 0.0f);

}

//スイッチが押されたとき
void CActivePillar::onSwitch(void) {

	if (!m_isActive) {
		m_isActive = true;
	}

}


//上側ピラーの移動
void CActivePillar::MoveTopPillar(void) {

	if (m_bDir[0]) {//上に移動

		m_pPillar[0].p.y += PILLAR_MOVESPEED;
		m_pPillar[0].p.y = min(m_pPillar[0].p.y, m_endPos[0].y);

	}
	else {			//下に移動

		m_pPillar[0].p.y -= PILLAR_MOVESPEED;
		m_pPillar[0].p.y = max(m_pPillar[0].p.y, m_startPos[0].y);

	}


	if (m_pPillar[0].p.y == m_startPos[0].y) {
		m_bDir[0] = true;
	}

	if (m_pPillar[0].p.y == m_endPos[0].y) {
		m_bDir[0] = false;
	}

}

//下側ピラーの移動
void CActivePillar::MoveBottomPillar(void) {

	if (m_bDir[1]) {//下に移動

		m_pPillar[1].p.y -= PILLAR_MOVESPEED;
		m_pPillar[1].p.y = max(m_pPillar[1].p.y, m_endPos[1].y);

	}
	else {			//上に移動

		m_pPillar[1].p.y += PILLAR_MOVESPEED;
		m_pPillar[1].p.y = min(m_pPillar[1].p.y, m_startPos[1].y);

	}


	if (m_pPillar[1].p.y == m_startPos[1].y) {
		m_bDir[1] = true;
	}

	if (m_pPillar[1].p.y == m_endPos[1].y) {
		m_bDir[1] = false;
	}

}


