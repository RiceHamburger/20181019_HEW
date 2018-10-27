//=====================================================================//
//		�X�v���C�g���� [sprite.cpp]                                    //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/07/05            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "sprite.h"


//=====================================================================//
//                                                                     //
//                          �|���S���`��p                             //
//                                                                     //
//=====================================================================//
/* --------------------------------
�R���X�g���N�^
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
�f�X�g���N�^
-------------------------------- */
Sprite::~Sprite() {}
//=====================================================================//
//                                                                     //
//                  �|���S�����S�_XY�ƃT�C�Y�Z�b�g�p                   //
//                                                                     //
//=====================================================================//
void Sprite::SetPos(D3DXVECTOR2 vec, int Width, int Height)
{
	/* --------------------------------
	���S���W�Z�b�g
	-------------------------------- */
	m_pos.pos = vec;
	/* --------------------------------
	�|���S�������ƍ����Z�b�g
	-------------------------------- */
	m_pos.width = Width;
	m_pos.height = Height;
}
//=====================================================================//
//                                                                     //
//                  �|���S�����S�_XY�ƃT�C�Y�Q�b�g�p                   //
//                                                                     //
//=====================================================================//
S_Vec Sprite::GetPos(void)
{
	return m_pos;
}

//=====================================================================//
//                                                                     //
//                          �|���S���摜�����p                         //
//                                                                     //
//=====================================================================//
void Sprite::SetDivide(int DivU, int DivV)
{
	/* --------------------------------
	UV�����Z�b�g
	-------------------------------- */
	m_uv.divU = DivU;
	m_uv.divV = DivV;
}
//=====================================================================//
//                                                                     //
//                 �|���S��UV�t���[���Z�b�g�p                          //
//                                                                     //
//=====================================================================//
void Sprite::SetUVNum(float NumU, float NumV)
{
	/* --------------------------------
	UV�t���[���ϊ��p�Z�b�g
	-------------------------------- */
	m_uv.numU = NumU;
	m_uv.numV = NumV;
}
//=====================================================================//
//                                                                     //
//								UV����								   //
//                                                                     //
//=====================================================================//
S_UV Sprite::GetUV(void)
{
	return m_uv;
}

//=====================================================================//
//                                                                     //
//						 �|���S����]�p�x�Z�b�g�p                      //
//                                                                     //
//=====================================================================//
void Sprite::SetRotate(float Rotate)
{
	/* --------------------------------
	��]�p�x�Z�b�g
	-------------------------------- */
	m_rotate = Rotate;
}
//=====================================================================//
//                                                                     //
//						 �|���S�����Z�b�g�p							   //
//                                                                     //
//=====================================================================//
void Sprite::SetAlpha(int alpha)
{
	/* --------------------------------
	���Z�b�g
	-------------------------------- */
	m_spriteVertex.color = D3DCOLOR_RGBA(255, 255, 255, alpha);
	return;
}

//=====================================================================//
//                                                                     //
//                          �|���S���`��	                           //
//                                                                     //
//=====================================================================//
void Sprite::Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn)
{
	/* --------------------------------
	���_���Z�b�g
	-------------------------------- */
	S_SpriteVertex vtx[4] = {
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)m_uv.numU / m_uv.divU : (float)(m_uv.numU + 1) / m_uv.divU), (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)m_uv.numU / m_uv.divU : (float)(m_uv.numU + 1) / m_uv.divU), (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y - (float)(m_pos.height) , 0.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)(m_uv.numU + 1) / m_uv.divU : (float)m_uv.numU / m_uv.divU), (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x - (float)(m_pos.width) , m_pos.pos.y + (float)(m_pos.height) , 0.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)(m_uv.numU + 1) / m_uv.divU : (float)m_uv.numU / m_uv.divU), (float)(m_uv.numV + 1) / m_uv.divV }
	};

	/* --------------------------------
	��]�v�Z�p
	-------------------------------- */
	for (int i = 0; i < 4; ++i) {
		float x = (vtx[i].x - m_pos.pos.x) * cos(m_rotate) - (vtx[i].y - m_pos.pos.y) * sin(m_rotate);
		float y = (vtx[i].x - m_pos.pos.x) * sin(m_rotate) + (vtx[i].y - m_pos.pos.y) * cos(m_rotate);
		/* -------------------m_pos.-------------					
		���S���W�Ȃ��ō���Ō�m_pos.�_�Ƃ��ĉ�]					
		-------------------------------- */
		vtx[i].x = x + m_pos.pos.x;
		vtx[i].y = y + m_pos.pos.y;
	}
	/* --------------------------------
	�e�N�X�`���Z�b�g
	-------------------------------- */
	pDevice3D->SetTexture(0, pTexture);
	/* --------------------------------
	���_�\���̐錾�Z�b�g
	-------------------------------- */
	pDevice3D->SetFVF(SPRITE_FVF);
	/* --------------------------------
	�X�v���C�g�`��
	-------------------------------- */
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(S_SpriteVertex));
}

//=====================================================================//
//                                                                     //
//                          �|���S���`��i��]�p�j	                   //
//                                                                     //
//=====================================================================//

void Sprite::Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn, float xo, float yo)
{
	/* --------------------------------
	���_���Z�b�g
	-------------------------------- */
	S_SpriteVertex vtx[4] = {
		{ m_pos.pos.x + m_pos.width / 2, m_pos.pos.y - m_pos.height / 2, 1.0f, 1.0f,m_spriteVertex.color, (isTurn ? (float)m_uv.numU / m_uv.divU : (float)(m_uv.numU + 1) / m_uv.divU), (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x + m_pos.width / 2, m_pos.pos.y + m_pos.height / 2, 1.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)m_uv.numU / m_uv.divU : (float)(m_uv.numU + 1) / m_uv.divU), (float)(m_uv.numV + 1) / m_uv.divV },
		{ m_pos.pos.x - m_pos.width / 2, m_pos.pos.y - m_pos.height / 2, 1.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)(m_uv.numU + 1) / m_uv.divU : (float)m_uv.numU / m_uv.divU), (float)m_uv.numV / m_uv.divV },
		{ m_pos.pos.x - m_pos.width / 2, m_pos.pos.y + m_pos.height / 2, 1.0f, 1.0f,m_spriteVertex.color,(isTurn ? (float)(m_uv.numU + 1) / m_uv.divU : (float)m_uv.numU / m_uv.divU), (float)(m_uv.numV + 1) / m_uv.divV }
	};
	/* --------------------------------
	��]�v�Z�p
	-------------------------------- */
	if (xo != 0)
	{
		for (int i = 0; i < 4; ++i) {
			float x = xo * cos(m_rotate) - yo * sin(m_rotate);
			float y = xo * sin(m_rotate) + yo * cos(m_rotate);
			/* --------------------------------
			���S���W�Ȃ��ō���Ō��_�Ƃ��ĉ�]
			-------------------------------- */
			vtx[i].x = x + m_pos.pos.x;
			vtx[i].y = y + m_pos.pos.y;
		}
	}

	/* --------------------------------
	�e�N�X�`���Z�b�g
	-------------------------------- */
	pDevice3D->SetTexture(0, pTexture);
	/* --------------------------------
	���_�\���̐錾�Z�b�g
	-------------------------------- */
	pDevice3D->SetFVF(SPRITE_FVF);
	/* --------------------------------
	�X�v���C�g�`��
	-------------------------------- */
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(S_SpriteVertex));
}




//=====================================================================//
//                                                                     //
//                          �����_�[�ύX�p                             //
//                                                                     //
//=====================================================================//
// �����_�[�X�e�[�g�̕ύX
void SetRenderState(IDirect3DDevice9* pD3DDevice, e_RENDERSTATE RenderState)
{
	/* --------------------------------
	�����_�����O�w��p
	-------------------------------- */
	switch (RenderState)
	{
	/* --------------------------------
	�����_�����O�@�f�t�H���g
	-------------------------------- */
	case RENDER_DEFAULT:
	{
		// �s�����I�u�W�F�N�g
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			//�A���t�@�u�����f�B���O�̖�����
	}
	break;
	/* --------------------------------
	�����_�����O�@����
	-------------------------------- */
	case RENDER_ALPHATEST:
	{
		// ���e�X�g�ɂ�铧���̈�̐؂蔲��
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//�u�����f�B���O�I�v�V�������Z
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
		// ���e�X�g�ɂ�铧���̈�̐؂蔲��
		//pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//�A���t�@�e�X�g�̗L����
		//pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);					//�A���t�@�Q�ƒl
		//pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//�A���t�@�e�X�g���i�
		//pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			//�A���t�@�u�����f�B���O�̖�����
	}
	break;
	/* --------------------------------
	�����_�����O�@�����Z
	-------------------------------- */
	case RENDER_HALFADD:
	{
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//�A���t�@�u�����f�B���O�̗L����
		pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				//Z�o�b�t�@�ւ̏������݂𖳌��ɂ���B
																			//pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );			//Z�e�X�g���s��Ȃ�			
																			//pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );				//���C�e�B���O���Ȃ�
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//�u�����f�B���O�I�v�V�������Z
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//SRC�̐ݒ�
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DEST�̐ݒ�

	}
	break;
	/* --------------------------------
	�����_�����O�@�t���[���Z����
	-------------------------------- */
	case RENDER_ADD:
	{
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//�A���t�@�u�����f�B���O�̗L����
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//�u�����f�B���O�I�v�V�������Z
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);			//SRC�̐ݒ�
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DEST�̐ݒ�
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
	}
	break;
	}
}
