//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "sprite3D.h"
#include "DirectX3D.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
Sprite3D::Sprite3D()
{
	m_spriteVertex.color = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_pos.pos = D3DXVECTOR2(0.0f, 0.0f);
	m_pos.height = 0;
	m_pos.width = 0;
	m_uv.divU = 0;
	m_uv.divV = 0;
	m_uv.numU = 0;
	m_uv.numV = 0;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
Sprite3D::~Sprite3D() {}


//*****************************************************************************
//中心点座標設定
//*****************************************************************************
void Sprite3D::SetPos(D3DXVECTOR2 vec, int Width, int Height)
{
	//中心点座標
	m_pos.pos = vec;
	
	//Spriteサイズ
	m_pos.width = Width;
	m_pos.height = Height;
}

//*****************************************************************************
//中心点座標を取る
//*****************************************************************************
S_3DVec Sprite3D::GetPos(void)
{
	return m_pos;
}

//*****************************************************************************
//SpriteUV分割数
//*****************************************************************************
void Sprite3D::SetDivide(int DivU, int DivV)
{
	m_uv.divU = DivU;
	m_uv.divV = DivV;
}

//*****************************************************************************
//SpriteUVフレーム
//*****************************************************************************
void Sprite3D::SetUVNum(float NumU, float NumV)
{
	m_uv.numU = NumU;
	m_uv.numV = NumV;
}

//*****************************************************************************
// アルファ設定
//*****************************************************************************
void Sprite3D::SetAlpha(int alpha)
{
	m_spriteVertex.color = D3DCOLOR_RGBA(255, 255, 255, alpha);
	return;
}


//*****************************************************************************
// 描画
//*****************************************************************************
void Sprite3D::Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture)
{
	/* --------------------------------
	頂点情報設定
	-------------------------------- */
	S_3DSpriteVertex vtx[6] = {
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
	};

	//テクスチャの設定
	pDevice3D->SetTexture(0, pTexture);

	//ライトの設定
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//頂点構造体宣言セット
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vtx, sizeof(vtx[0]));
}

void Sprite3D::Draw(k_Texture index, RectC2D pos, float depth) {

	S_3DSpriteVertex vtx[6] = {
		{ pos.p.x + (float)(pos.hl.x) , pos.p.y + (float)(pos.hl.y) , depth ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ pos.p.x + (float)(pos.hl.x) , pos.p.y - (float)(pos.hl.y) , depth ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ pos.p.x - (float)(pos.hl.x) , pos.p.y + (float)(pos.hl.y) , depth ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ pos.p.x + (float)(pos.hl.x) , pos.p.y - (float)(pos.hl.y) , depth ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ pos.p.x - (float)(pos.hl.x) , pos.p.y - (float)(pos.hl.y) , depth ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ pos.p.x - (float)(pos.hl.x) , pos.p.y + (float)(pos.hl.y) , depth ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
	};

	LPDIRECT3DDEVICE9 pDevice3D = DirectX3DGetDevice();

	//テクスチャの設定
	pDevice3D->SetTexture(0, DirectX3DGetTEXTURE(index));

	//ライトの設定
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//頂点構造体宣言セット
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vtx, sizeof(vtx[0]));


}

//描画 : 三角形
void Sprite3D::Draw(k_Texture index, Triangle2D pos, float depth, D3DCOLOR color) {


	S_3DSpriteVertex vtx[3] = {
		{ pos.p[0].x , pos.p[0].y , depth ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ pos.p[1].x , pos.p[1].y , depth ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ pos.p[2].x , pos.p[2].y , depth ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
	};

	LPDIRECT3DDEVICE9 pDevice3D = DirectX3DGetDevice();

	//テクスチャの設定
	pDevice3D->SetTexture(0, DirectX3DGetTEXTURE(index));

	//ライトの設定
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//頂点構造体宣言セット
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, vtx, sizeof(vtx[0]));
}


//*****************************************************************************
// 描画
//*****************************************************************************
void Sprite3D::DrawRotate(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, FLOAT rotate)
{
	/* --------------------------------
	頂点情報設定
	-------------------------------- */
	S_3DSpriteVertex vtx[6] =
	{
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
	};

	/* --------------------------------
	回転計算用
	-------------------------------- */
	for (int i = 0; i < 6; ++i)
	{
		float x = (vtx[i].x - m_pos.pos.x) * cos(rotate) - (vtx[i].y - m_pos.pos.y) * sin(rotate);
		float y = (vtx[i].x - m_pos.pos.x) * sin(rotate) + (vtx[i].y - m_pos.pos.y) * cos(rotate);
		/* -------------------m_pos.-------------
		中心座標なしで左上で原m_pos.点として回転
		-------------------------------- */
		vtx[i].x = x + m_pos.pos.x;
		vtx[i].y = y + m_pos.pos.y;

	}


	//テクスチャの設定
	pDevice3D->SetTexture(0, pTexture);

	//ライトの設定
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//頂点構造体宣言セット
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vtx, sizeof(vtx[0]));
}

void Sprite3D::Draw(k_Texture pTexture)
{
	/* --------------------------------
	頂点情報設定
	-------------------------------- */
	S_3DSpriteVertex vtx[6] = {
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
	};

	LPDIRECT3DDEVICE9 pDevice3D = DirectX3DGetDevice();

	//テクスチャの設定
	pDevice3D->SetTexture(0, DirectX3DGetTEXTURE(pTexture));

	//ライトの設定
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//頂点構造体宣言セット
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vtx, sizeof(vtx[0]));
}

void Sprite3D::SetColor(D3DCOLOR color)
{
	m_spriteVertex.color = color;
}