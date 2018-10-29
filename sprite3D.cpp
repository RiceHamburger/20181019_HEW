//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "sprite3D.h"
#include "DirectX3D.h"

//*****************************************************************************
//�R���X�g���N�^
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
//�f�X�g���N�^
//*****************************************************************************
Sprite3D::~Sprite3D() {}


//*****************************************************************************
//���S�_���W�ݒ�
//*****************************************************************************
void Sprite3D::SetPos(D3DXVECTOR2 vec, int Width, int Height)
{
	//���S�_���W
	m_pos.pos = vec;
	
	//Sprite�T�C�Y
	m_pos.width = Width;
	m_pos.height = Height;
}

//*****************************************************************************
//���S�_���W�����
//*****************************************************************************
S_3DVec Sprite3D::GetPos(void)
{
	return m_pos;
}

//*****************************************************************************
//SpriteUV������
//*****************************************************************************
void Sprite3D::SetDivide(int DivU, int DivV)
{
	m_uv.divU = DivU;
	m_uv.divV = DivV;
}

//*****************************************************************************
//SpriteUV�t���[��
//*****************************************************************************
void Sprite3D::SetUVNum(float NumU, float NumV)
{
	m_uv.numU = NumU;
	m_uv.numV = NumV;
}

//*****************************************************************************
// �A���t�@�ݒ�
//*****************************************************************************
void Sprite3D::SetAlpha(int alpha)
{
	m_spriteVertex.color = D3DCOLOR_RGBA(255, 255, 255, alpha);
	return;
}


//*****************************************************************************
// �`��
//*****************************************************************************
void Sprite3D::Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture)
{
	/* --------------------------------
	���_���ݒ�
	-------------------------------- */
	S_3DSpriteVertex vtx[6] = {
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
	};

	//�e�N�X�`���̐ݒ�
	pDevice3D->SetTexture(0, pTexture);

	//���C�g�̐ݒ�
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//���_�\���̐錾�Z�b�g
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//�X�v���C�g�`��
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

	//�e�N�X�`���̐ݒ�
	pDevice3D->SetTexture(0, DirectX3DGetTEXTURE(index));

	//���C�g�̐ݒ�
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//���_�\���̐錾�Z�b�g
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//�X�v���C�g�`��
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vtx, sizeof(vtx[0]));


}

//�`�� : �O�p�`
void Sprite3D::Draw(k_Texture index, Triangle2D pos, float depth, D3DCOLOR color) {


	S_3DSpriteVertex vtx[3] = {
		{ pos.p[0].x , pos.p[0].y , depth ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)m_uv.numV / m_uv.divV },
		{ pos.p[1].x , pos.p[1].y , depth ,m_spriteVertex.color ,(float)(m_uv.numU + 1) / m_uv.divU, (float)(m_uv.numV + 1) / m_uv.divV },
		{ pos.p[2].x , pos.p[2].y , depth ,m_spriteVertex.color ,(float)m_uv.numU / m_uv.divU, (float)m_uv.numV / m_uv.divV },
	};

	LPDIRECT3DDEVICE9 pDevice3D = DirectX3DGetDevice();

	//�e�N�X�`���̐ݒ�
	pDevice3D->SetTexture(0, DirectX3DGetTEXTURE(index));

	//���C�g�̐ݒ�
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//���_�\���̐錾�Z�b�g
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//�X�v���C�g�`��
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, vtx, sizeof(vtx[0]));
}


//*****************************************************************************
// �`��
//*****************************************************************************
void Sprite3D::DrawRotate(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, FLOAT rotate)
{
	/* --------------------------------
	���_���ݒ�
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
	��]�v�Z�p
	-------------------------------- */
	for (int i = 0; i < 6; ++i)
	{
		float x = (vtx[i].x - m_pos.pos.x) * cos(rotate) - (vtx[i].y - m_pos.pos.y) * sin(rotate);
		float y = (vtx[i].x - m_pos.pos.x) * sin(rotate) + (vtx[i].y - m_pos.pos.y) * cos(rotate);
		/* -------------------m_pos.-------------
		���S���W�Ȃ��ō���Ō�m_pos.�_�Ƃ��ĉ�]
		-------------------------------- */
		vtx[i].x = x + m_pos.pos.x;
		vtx[i].y = y + m_pos.pos.y;

	}


	//�e�N�X�`���̐ݒ�
	pDevice3D->SetTexture(0, pTexture);

	//���C�g�̐ݒ�
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//���_�\���̐錾�Z�b�g
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//�X�v���C�g�`��
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vtx, sizeof(vtx[0]));
}

void Sprite3D::Draw(k_Texture pTexture)
{
	/* --------------------------------
	���_���ݒ�
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

	//�e�N�X�`���̐ݒ�
	pDevice3D->SetTexture(0, DirectX3DGetTEXTURE(pTexture));

	//���C�g�̐ݒ�
	pDevice3D->SetRenderState(D3DRS_LIGHTING, false);

	//���_�\���̐錾�Z�b�g
	pDevice3D->SetFVF(SPRITE3D_FVF);

	//�X�v���C�g�`��
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vtx, sizeof(vtx[0]));
}

void Sprite3D::SetColor(D3DCOLOR color)
{
	m_spriteVertex.color = color;
}