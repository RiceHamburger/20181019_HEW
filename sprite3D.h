//=============================================================================
//
// Sprite3D�N���X [sprite3D.h]
// Sprite�e�X�g�p
//										Autor:��
//										Date:2018/10/08
//=============================================================================
#ifndef SPRITE3D_H
#define SPRITE3D_H

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <d3dx9.h>
#include "Primitive2D.h"
#include "Texture.h"

typedef struct
{
	float x, y, z;
	D3DCOLOR color;
	float u, v;
}S_3DSpriteVertex;

typedef struct{
	D3DXVECTOR2 pos;
	float width;
	float height;
}S_3DVec;

typedef struct{
	//UV�̕�����
	int divU;
	int divV;

	//UV�̔ԍ�
	float numU;
	float numV;
}S_3DUV;

//*****************************************************************************
// Sprite3D�N���X
//*****************************************************************************
class Sprite3D
{
private:
	static const DWORD SPRITE3D_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

	S_3DSpriteVertex m_spriteVertex;

	S_3DVec m_pos;

	S_3DUV m_uv;

public:
	Sprite3D();
	~Sprite3D();

	void SetPos(D3DXVECTOR2 vec, int Width, int Height);
	S_3DVec GetPos(void);

	void SetAlpha(int alpha);

	void SetDivide(int DivU, int DivV);
	void SetUVNum(float NumU, float NumV);

	//�`��
	void Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture);

	//�`��
	void Draw(k_Texture index, RectC2D pos, float depth);

	//�`�� : �O�p�`
	//void Draw(k_Texture index, Triangle2D pos, float depth, D3DCOLOR color);
};

#endif