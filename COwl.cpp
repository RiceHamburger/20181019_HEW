/*====================================================================================

	�I�E���N���X�܂Ƃ߁@ [COwl.cpp]
																Autor	: ����
																Date	: 2018/10/22
--------------------------------------------------------------------------------------
�R�����g:
--------------------------------------------------------------------------------------
�C������:
====================================================================================*/


/*--------------------------------------------------------------------------------------
	�C���N���[�h�t�@�C��
--------------------------------------------------------------------------------------*/
#include "COwl.h"

/*--------------------------------------------------------------------------------------
	�񋓌^ : �\����
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	�}�N����`
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	�N���X���s����
--------------------------------------------------------------------------------------*/

/*-------------------------------------------
	�T�[�`���C�g�N���X
-------------------------------------------*/

//�R���X�g���N�^ : �f�t�H���g
CSearchLight::CSearchLight(Float2 p1, Float2 p2, Float2 p3, D3DCOLOR color) {

	//���W�̐ݒ�
	m_pos.p[0] = p1;
	m_pos.p[1] = p2;
	m_pos.p[2] = p3;

	//�J���[�̐ݒ�
	m_color = color;

}

//�`��
void CSearchLight::Draw(void) {

}


/*-------------------------------------------
	�I�E�����N���X
-------------------------------------------*/

//�R���X�g���N�^ : ������
COwl::COwl(Float2 p, Float2 size, k_Texture index) {

	//���W�̐ݒ�
	pos.p = p;

	//�T�C�Y�̐ݒ�
	pos.hl = size;

	//�e�N�X�`���̐ݒ�
	m_textureIndex = index;

}

//�T�[�`���C�g�̐���
void COwl::CreateSearchLight(Float2 p1, Float2 p2, Float2 p3 , D3DCOLOR color) {

	//�T�[�`���C�g�����łɐ�������Ă��Ȃ���ΐ���
	if (m_pLight) {
		m_pLight = new CSearchLight(p1, p2, p3, color);
	}

}

//�`��
void COwl::Draw(void) {

	//�t�N���E�̕`��
	Sprite3D::Draw(m_textureIndex, pos, 0.0f);

	//�T�[�`���C�g�����݂���Ȃ�`��
	if (m_pLight) {
		m_pLight->Draw();
	}
}

//�f�X�g���N�^
COwl::~COwl() {

	if (m_pLight) {

		//�������̉��
		delete m_pLight;

	}
}


/*-------------------------------------------
	�A�N�e�B�u�I�E���N���X
-------------------------------------------*/

//�R���X�g���N�^ : �f�t�H���g
CActiveOwl::CActiveOwl(Float2 pos, Float2 size, k_Texture index, int lightInterval) : COwl(pos , size , index){

	//���C�g�C���^�[�o���̐ݒ�
	m_lightInterval = lightInterval;

}

//�A�b�v�f�[�g
bool CActiveOwl::Update() {


	return m_bAlive;
}


/*-------------------------------------------
	�X�^�e�B�b�N�I�E���N���X
-------------------------------------------*/

//�R���X�g���N�^ : �f�t�H���g
CStaticOwl::CStaticOwl(Float2 pos, Float2 size, k_Texture index) : COwl(pos , size , index){

	//�T�[�`���C�g�̐���

	//�T�[�`���C�g�t���O���I��
	m_isLight = true;

}

//�A�b�v�f�[�g
bool CStaticOwl::Update() {

	//�T�[�`���C�g�t���O���I�t�̏ꍇ�T�[�`���C�g�����
	if (!m_isLight) {

		//���������


	}

	return m_bAlive;
}

void CStaticOwl::onSwitch(void) {

	//�T�[�`���C�g�t���O���I���̏ꍇ�I�t�ɕύX
	if (m_isLight) {
		m_isLight = false;
	}
}
