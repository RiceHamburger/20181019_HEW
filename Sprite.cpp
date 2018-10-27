//=====================================================================//
//		スプライト処理 [sprite.cpp]                                    //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/07/05            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "sprite.h"


//=====================================================================//
//                                                                     //
//                          ポリゴン描画用                             //
//                                                                     //
//=====================================================================//
/* --------------------------------
コンストラクタ
-------------------------------- */
Sprite::Sprite()
{
	m_spriteVertex.color = 0xffffffff;
	m_rotate = 0.0f;
	m_pos.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_pos.height = 0;
	m_pos.width = 0;
	m_uv.divU = 0;
	m_uv.divV = 0;
	m_uv.numU = 0;
	m_uv.numV = 0;
}

/* --------------------------------
デストラクタ
-------------------------------- */
Sprite::~Sprite() {}
//=====================================================================//
//                                                                     //
//                  ポリゴン中心点XYとサイズセット用                   //
//                                                                     //
//=====================================================================//
void Sprite::SetPos(D3DXVECTOR2 vec, int Width, int Height)
{
	/* --------------------------------
	中心座標セット
	-------------------------------- */
	m_pos.pos = vec;
	/* --------------------------------
	ポリゴン長さと高さセット
	-------------------------------- */
	m_pos.width = Width;
	m_pos.height = Height;
}
//=====================================================================//
//                                                                     //
//                  ポリゴン中心点XYとサイズゲット用                   //
//                                                                     //
//=====================================================================//
S_Vec Sprite::GetPos(void)
{
	return m_pos;
}

//=====================================================================//
//                                                                     //
//                          ポリゴン画像等分用                         //
//                                                                     //
//=====================================================================//
void Sprite::SetDivide(int DivU, int DivV)
{
	/* --------------------------------
	UV等分セット
	-------------------------------- */
	m_uv.divU = DivU;
	m_uv.divV = DivV;
}
//=====================================================================//
//                                                                     //
//                 ポリゴンUVフレームセット用                          //
//                                                                     //
//=====================================================================//
void Sprite::SetUVNum(float NumU, float NumV)
{
	/* --------------------------------
	UVフレーム変換用セット
	-------------------------------- */
	m_uv.numU = NumU;
	m_uv.numV = NumV;
}
//=====================================================================//
//                                                                     //
//								UV処理								   //
//                                                                     //
//=====================================================================//
S_UV Sprite::GetUV(void)
{
	return m_uv;
}

//=====================================================================//
//                                                                     //
//						 ポリゴン回転角度セット用                      //
//                                                                     //
//=====================================================================//
void Sprite::SetRotate(float Rotate)
{
	/* --------------------------------
	回転角度セット
	-------------------------------- */
	m_rotate = Rotate;
}
//=====================================================================//
//                                                                     //
//						 ポリゴンαセット用							   //
//                                                                     //
//=====================================================================//
void Sprite::SetAlpha(int alpha)
{
	/* --------------------------------
	αセット
	-------------------------------- */
	m_spriteVertex.color = D3DCOLOR_RGBA(255, 255, 255, alpha);
	return;
}

//=====================================================================//
//                                                                     //
//                          ポリゴン描画	                           //
//                                                                     //
//=====================================================================//
void Sprite::Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn)
{
	/* --------------------------------
	頂点情報セット
	-------------------------------- */
	S_SpriteVertex vtx[4] = {
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)m_uv.numU / m_uv.divU : (float)(m_uv.numU + 1) / m_uv.divU), (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)m_uv.numU / m_uv.divU : (float)(m_uv.numU + 1) / m_uv.divU), (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)(m_uv.numU + 1) / m_uv.divU : (float)m_uv.numU / m_uv.divU), (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)(m_uv.numU + 1) / m_uv.divU : (float)m_uv.numU / m_uv.divU), (float)(m_uv.numV + 1) / m_uv.divV }
	};

	/* --------------------------------
	回転計算用
	-------------------------------- */
	for (int i = 0; i < 4; ++i) {
		float x = (vtx[i].x - m_pos.pos.x) * cos(m_rotate) - (vtx[i].y - m_pos.pos.y) * sin(m_rotate);
		float y = (vtx[i].x - m_pos.pos.x) * sin(m_rotate) + (vtx[i].y - m_pos.pos.y) * cos(m_rotate);
		/* -------------------m_pos.-------------					
		中心座標なしで左上で原m_pos.点として回転					
		-------------------------------- */
		vtx[i].x = x + m_pos.pos.x;
		vtx[i].y = y + m_pos.pos.y;
	}
	/* --------------------------------
	テクスチャセット
	-------------------------------- */
	pDevice3D->SetTexture(0, pTexture);
	/* --------------------------------
	頂点構造体宣言セット
	-------------------------------- */
	pDevice3D->SetFVF(SPRITE_FVF);
	/* --------------------------------
	スプライト描画
	-------------------------------- */
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(S_SpriteVertex));
}

//=====================================================================//
//                                                                     //
//                          ポリゴン描画（回転用）	                   //
//                                                                     //
//=====================================================================//

void Sprite::Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn, float xo, float yo)
{
	/* --------------------------------
	頂点情報セット
	-------------------------------- */
	S_SpriteVertex vtx[4] = {
		{ m_pos.pos.x + m_pos.width / 2, m_pos.pos.y - m_pos.height / 2, 1.0f, 1.0f,m_spriteVertex.color, (isTurn ? (float)m_uv.numU / m_uv.divU : (float)(m_uv.numU + 1) / m_uv.divU), (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + m_pos.width / 2, m_pos.pos.y + m_pos.height / 2, 1.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)m_uv.numU / m_uv.divU : (float)(m_uv.numU + 1) / m_uv.divU), (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - m_pos.width / 2, m_pos.pos.y - m_pos.height / 2, 1.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)(m_uv.numU + 1) / m_uv.divU : (float)m_uv.numU / m_uv.divU), (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x - m_pos.width / 2, m_pos.pos.y + m_pos.height / 2, 1.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)(m_uv.numU + 1) / m_uv.divU : (float)m_uv.numU / m_uv.divU), (float)(m_uv.numV + 1) / m_uv.divV }
	};
	/* --------------------------------
	回転計算用
	-------------------------------- */
	if (xo != 0)
	{
		for (int i = 0; i < 4; ++i) {
			float x = xo * cos(m_rotate) - yo * sin(m_rotate);
			float y = xo * sin(m_rotate) + yo * cos(m_rotate);
			/* --------------------------------
			中心座標なしで左上で原点として回転
			-------------------------------- */
			vtx[i].x = x + m_pos.pos.x;
			vtx[i].y = y + m_pos.pos.y;
		}
	}

	/* --------------------------------
	テクスチャセット
	-------------------------------- */
	pDevice3D->SetTexture(0, pTexture);
	/* --------------------------------
	頂点構造体宣言セット
	-------------------------------- */
	pDevice3D->SetFVF(SPRITE_FVF);
	/* --------------------------------
	スプライト描画
	-------------------------------- */
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(S_SpriteVertex));
}




//=====================================================================//
//                                                                     //
//                          レンダー変更用                             //
//                                                                     //
//=====================================================================//
// レンダーステートの変更
void SetRenderState(IDirect3DDevice9* pD3DDevice, e_RENDERSTATE RenderState)
{
	/* --------------------------------
	レンダリング指定用
	-------------------------------- */
	switch (RenderState)
	{
	/* --------------------------------
	レンダリング　デフォルト
	-------------------------------- */
	case RENDER_DEFAULT:
	{
		// 不透明オブジェクト
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			//アルファブレンディングの無効化
	}
	break;
	/* --------------------------------
	レンダリング　透明
	-------------------------------- */
	case RENDER_ALPHATEST:
	{
		// αテストによる透明領域の切り抜き
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//ブレンディングオプション加算
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
		// αテストによる透明領域の切り抜き
		//pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//アルファテストの有効化
		//pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);					//アルファ参照値
		//pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//アルファテスト合格基準
		//pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			//アルファブレンディングの無効化
	}
	break;
	/* --------------------------------
	レンダリング　半加算
	-------------------------------- */
	case RENDER_HALFADD:
	{
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//アルファブレンディングの有効化
		pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				//Zバッファへの書き込みを無効にする。
																			//pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );			//Zテストを行わない			
																			//pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );				//ライティングしない
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//ブレンディングオプション加算
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//SRCの設定
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DESTの設定

	}
	break;
	/* --------------------------------
	レンダリング　フルー加算合成
	-------------------------------- */
	case RENDER_ADD:
	{
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//アルファブレンディングの有効化
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//ブレンディングオプション加算
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);			//SRCの設定
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DESTの設定
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
	}
	break;
	}
}
