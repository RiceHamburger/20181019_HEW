/*====================================================================================

	�A�N�e�B�u�s���[�N���X�@ [CActivePillar.cpp]
																Autor	: ����
																Date	: 2018/10/27
--------------------------------------------------------------------------------------
�R�����g:
--------------------------------------------------------------------------------------
�C������:
====================================================================================*/


/*--------------------------------------------------------------------------------------
	�C���N���[�h�t�@�C��
--------------------------------------------------------------------------------------*/
#include "CActivePillar.h"

/*--------------------------------------------------------------------------------------
	�񋓌^ : �\����
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	�}�N����`
--------------------------------------------------------------------------------------*/
#define PILLAR_MOVESPEED	(10.0f)
/*--------------------------------------------------------------------------------------
	�N���X���s����
--------------------------------------------------------------------------------------*/

//�R���X�g���N�^ : �f�t�H���g
CActivePillar::CActivePillar(RectC2D pos) {

	//����̒��̐ݒ�
	//�㑤
	m_pPillar[0].p = Float2(pos.p.x , pos.p.y + (pos.hl.y / 2));
	m_pPillar[0].hl = pos.hl / 2;
	m_startPos[0] = m_pPillar[0].p;
	m_endPos[0] = Float2(pos.p.x, pos.p.y + (pos.hl.y * 2));
	m_bDir[0] = true;
	//����
	m_pPillar[1].p = Float2(pos.p.x, pos.p.y - (pos.hl.y / 2));
	m_pPillar[1].hl = pos.hl / 2;
	m_startPos[1] = m_pPillar[1].p;
	m_endPos[1] = Float2(pos.p.x, pos.p.y - (pos.hl.y * 2));
	m_bDir[1] = true;

	Sprite3D::SetDivide(1, 1);							    // �摜������
	Sprite3D::SetUVNum(0, 0);									// ����UV���W�ݒ�

	//�A�N�e�B�u�t���O��false�ɐݒ�
	m_isActive = true;

}

//�A�b�v�f�[�g
bool CActivePillar::Update() {

	//�A�N�e�B�u�t���O���^�ł���Γ�����s��
	if (m_isActive) {

		MoveTopPillar();

		MoveBottomPillar();
	}

	return true;
}

//�`��
void CActivePillar::Draw() {


	Sprite3D::Draw(k_kobeni, m_pPillar[0], 0.0f);
	Sprite3D::Draw(k_kobeni, m_pPillar[1], 0.0f);

}

//�X�C�b�`�������ꂽ�Ƃ�
void CActivePillar::onSwitch(void) {

	if (!m_isActive) {
		m_isActive = true;
	}

}


//�㑤�s���[�̈ړ�
void CActivePillar::MoveTopPillar(void) {

	if (m_bDir[0]) {//��Ɉړ�

		m_pPillar[0].p.y += PILLAR_MOVESPEED;
		m_pPillar[0].p.y = min(m_pPillar[0].p.y, m_endPos[0].y);

	}
	else {			//���Ɉړ�

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

//�����s���[�̈ړ�
void CActivePillar::MoveBottomPillar(void) {

	if (m_bDir[1]) {//���Ɉړ�

		m_pPillar[1].p.y -= PILLAR_MOVESPEED;
		m_pPillar[1].p.y = max(m_pPillar[1].p.y, m_endPos[1].y);

	}
	else {			//��Ɉړ�

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


