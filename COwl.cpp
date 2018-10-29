/*====================================================================================

	オウルクラスまとめ　 [COwl.cpp]
																Autor	: 西口
																Date	: 2018/10/22
--------------------------------------------------------------------------------------
コメント:
--------------------------------------------------------------------------------------
修正日時:
====================================================================================*/


/*--------------------------------------------------------------------------------------
	インクルードファイル
--------------------------------------------------------------------------------------*/
#include "COwl.h"

/*--------------------------------------------------------------------------------------
	列挙型 : 構造体
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	マクロ定義
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	クラス実行部分
--------------------------------------------------------------------------------------*/

/*-------------------------------------------
	サーチライトクラス
-------------------------------------------*/

//コンストラクタ : デフォルト
CSearchLight::CSearchLight(Float2 p1, Float2 p2, Float2 p3, D3DCOLOR color) {

	//座標の設定
	m_pos.p[0] = p1;
	m_pos.p[1] = p2;
	m_pos.p[2] = p3;

	//カラーの設定
	m_color = color;

	Sprite3D::SetDivide(1, 1);							    // 画像分割数
	Sprite3D::SetUVNum(0, 0);									// 現在UV座標設定


}

//描画
void CSearchLight::Draw(void) {

	Sprite3D::Draw(k_kobeni, m_pos, -0.1f , m_color);

}


/*-------------------------------------------
	オウル基底クラス
-------------------------------------------*/

//コンストラクタ : 初期化
COwl::COwl(Float2 p, Float2 size, k_Texture index) {

	//座標の設定
	pos.p = p;

	//サイズの設定
	pos.hl = size;

	//テクスチャの設定
	m_textureIndex = index;

	//サーチライトのポインター初期化
	m_pLight = NULL;

}

//サーチライトの生成
void COwl::CreateSearchLight(Float2 p1, Float2 p2, Float2 p3 , D3DCOLOR color) {

	//サーチライトがすでに生成されていなければ生成
	if (!m_pLight) {
		m_pLight = new CSearchLight(p1, p2, p3, color);
	}

}

//描画
void COwl::Draw(void) {

	//フクロウの描画
	Sprite3D::Draw(m_textureIndex, pos, 0.0f);

	//サーチライトが存在するなら描画
	if (m_pLight) {
		m_pLight->Draw();
	}
}

//デストラクタ
COwl::~COwl() {

	if (m_pLight) {

		//メモリの解放
		delete m_pLight;

	}
}


/*-------------------------------------------
	アクティブオウルクラス
-------------------------------------------*/

//コンストラクタ : デフォルト
CActiveOwl::CActiveOwl(Float2 pos, Float2 size, k_Texture index, int lightInterval) : COwl(pos , size , index){

	//ライトインターバルの設定
	m_lightInterval = lightInterval;

	//フレームカウントの初期化
	m_frameCount = NULL;

	Sprite3D::SetDivide(1, 1);							    // 画像分割数
	Sprite3D::SetUVNum(0, 0);									// 現在UV座標設定


}

//アップデート
bool CActiveOwl::Update() {

	if (m_frameCount == m_lightInterval) {

		if (m_pLight) {
			delete m_pLight;
			m_pLight = NULL;
			m_frameCount = NULL;
		}
		else {
			CreateSearchLight(Float2(700.0f , 715.0f), Float2(500.0f , 470.0f), Float2(250.0f , 470.0f), D3DCOLOR_RGBA(255, 255, 255, 255));
			m_frameCount = NULL;
		}
	}


	m_frameCount++;

	return m_bAlive;
}

void CActiveOwl::Draw() {
	//フクロウの描画
	Sprite3D::Draw(m_textureIndex, pos, 0.0f);

	//サーチライトが存在するなら描画
	if (m_pLight) {
		m_pLight->Draw();
	}

}


/*-------------------------------------------
	スタティックオウルクラス
-------------------------------------------*/

//コンストラクタ : デフォルト
CStaticOwl::CStaticOwl(Float2 pos, Float2 size, k_Texture index) : COwl(pos , size , index){

	//サーチライトの生成

	//サーチライトフラグをオン
	m_isLight = true;

}

//アップデート
bool CStaticOwl::Update() {

	//サーチライトフラグがオフの場合サーチライトを解放
	if (!m_isLight) {

		//メモリ解放


	}

	return m_bAlive;
}

void CStaticOwl::onSwitch(void) {

	//サーチライトフラグがオンの場合オフに変更
	if (m_isLight) {
		m_isLight = false;
	}
}

