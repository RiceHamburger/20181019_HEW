/*====================================================================================

	�v���C���[�N���X�@ [CPlayer.cpp]
																Autor	: ����
																Date	: 2018/09/25
--------------------------------------------------------------------------------------
�R�����g:
--------------------------------------------------------------------------------------
�C������:
====================================================================================*/


/*--------------------------------------------------------------------------------------
	�C���N���[�h�t�@�C��
--------------------------------------------------------------------------------------*/
#include "CPlayer.h"
#include "Texture.h"

/*--------------------------------------------------------------------------------------
	�񋓌^ : �\����
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
	�}�N����`
--------------------------------------------------------------------------------------*/

//#define GROUND_Y1					(800.0f)
//#define GROUND_Y2					(400.0f)
//#define GRAVITY						(0.8f)
//#define JUMP_VALUE					(-18.0f)

//*****************************************************************�M�����Ƃ���*****************************************************************************************
#define GROUND_Y1					(-15.0f)
#define GROUND_Y2					(465.0f)
#define GRAVITY						(-0.98f)
#define JUMP_VALUE					(20.0f)
#define X_AXIS_MAX					(3840.0f)
#define SQUATA_HEIGHT				(40.0f)
//*****************************************************************�M�����Ƃ���*****************************************************************************************

//�v���C���[1
#define INITIALIZE_POS_X			(120.0f)
#define INITIALIZE_POS_Y			(300.0f)
#define PLAYER_WIDTH				(25.0f)
#define PLAYER_HEIGHT				(50.0f)
#define INITIALIZE_VELOCITY_X		(0.0f)
#define INITIALIZE_VELOCITY_Y		(0.0f)
#define VECDIR_X					(0.9f)
#define ACCELERATION				(1.0f)
#define VELOCITY_RESIST				(0.9f)

//�v���C���[2
#define INITIALIZE_POS_X2			(120.0f)
#define INITIALIZE_POS_Y2			(600.0f)


#define SCREEN_WIDTH				(1600)
#define SCREEN_HEIGHT				(900)

/*--------------------------------------------------------------------------------------
	�N���X���s����
--------------------------------------------------------------------------------------*/

/*-------------------------------------------
	�v���C���[�N���X
-------------------------------------------*/

//
//	�����o���\�b�h
//
//*****************************************************************�M�����Ƃ���*****************************************************************************************
//�ÓI�����o�ϐ�
float CPlayer::axis_max = SCREEN_WIDTH;
float CPlayer::axis_min = 0;
//*****************************************************************�M�����Ƃ���*****************************************************************************************

//�R���X�g���N�^ : �f�t�H���g
CPlayer::CPlayer(int num) {

	//�ʒu�̐ݒ�
	switch (num) {
	case ONE:
		m_numPlayer = num;
		pos.p.x = INITIALIZE_POS_X;
		pos.p.y = INITIALIZE_POS_Y;
		break;
		
	case TWO:
		m_numPlayer = num;
		pos.p.x = INITIALIZE_POS_X2;
		pos.p.y = INITIALIZE_POS_Y2;
		break;
	}

	//�T�C�Y�̐ݒ�
	pos.hl.x = PLAYER_WIDTH;
	pos.hl.y = PLAYER_HEIGHT;



	//�e�N�X�`���̐ݒ�
	//m_textureIndex = ;

	//���x�̐ݒ�
	m_velocity.x = NULL;
	m_velocity.y = NULL;

	//�ړ������̐ݒ�
	m_vecDir.x = NULL;

	//�d�͂̐ݒ�
	m_vecDir.y = GRAVITY;

	//����G�Ă��邩�̔���
	m_hashiraue = false;

	//������
	//Sprite::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y), 64, 64);	// �iD3DXVECTOR2(XY���W),����,�����j��ݒ�
	//Sprite::SetDivide(1, 1);									// �摜������
	//Sprite::SetUVNum(0, 0);									// ����UV���W�ݒ�

	//*****************************************************************�M�����Ƃ���*****************************************************************************************
	Sprite3D::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y), pos.hl.x, pos.hl.y);	// �iD3DXVECTOR2(XY���W),����,�����j��ݒ�
	Sprite3D::SetDivide(1, 1);							    // �摜������
	Sprite3D::SetUVNum(0, 0);									// ����UV���W�ݒ�
	//*****************************************************************�M�����Ƃ���*****************************************************************************************
}




//�A�b�v�f�[�g
bool CPlayer::Update(void) {


	//�ړ��x�N�g���̐��K��
	//m_vecDir.norm();

	//���x�X�V
	m_velocity = m_velocity + m_vecDir * ACCELERATION;

	//�ʒu���̍X�V
	pos.p = pos.p + m_velocity;

	switch (m_numPlayer) {
	case ONE:
		//*****************************************************************�M�����Ƃ���*****************************************************************************************
		//��ʊO�␳
		//X��
		/*pos.p.x = max(0 + pos.hl.x, pos.p.x);*/
		//pos.p.x = min(pos.p.x, SCREEN_WIDTH - pos.hl.x);

		//Y��
		/*pos.p.y = max(0 + pos.hl.y, pos.p.y);
		pos.p.y = min(pos.p.y, GROUND_Y1 - pos.hl.y);*/

		//���n����
		/*if (pos.p.y >= GROUND_Y1 - pos.hl.y) {
			m_bJump = false;
			m_velocity.y = 0.0f;
		}
		else {
			m_bJump = true;
		}*/

		//X��
		pos.p.x = max(axis_min + pos.hl.x, pos.p.x);
		pos.p.x = min(pos.p.x, axis_max - pos.hl.x);

		//Y��
		pos.p.y = max(m_Ground + pos.hl.y, pos.p.y);
		pos.p.y = min(pos.p.y, SCREEN_HEIGHT - pos.hl.y);
		
		

		//���n����
		/*if (pos.p.y <= m_Ground + pos.hl.y && !m_Climb) {
			m_bJump = false;
			m_velocity.y = 0.0f;
		}
		else {
			m_bJump = true;
		}*/

		if (m_Squats) {
			pos.hl.y = SQUATA_HEIGHT;
		}
		else {
			pos.hl.y = PLAYER_HEIGHT;
		}

		//*****************************************************************�M�����Ƃ���*****************************************************************************************

		break;

	case TWO:
		//*****************************************************************�M�����Ƃ���*****************************************************************************************
		//��ʊO�␳
		//X��
		/*pos.p.x = max(0 + pos.hl.x, pos.p.x);
		pos.p.x = min(pos.p.x, SCREEN_WIDTH - pos.hl.x);*/

		//Y��
		/*pos.p.y = max(0 + pos.hl.y, pos.p.y);
		pos.p.y = min(pos.p.y, GROUND_Y2 - pos.hl.y);*/

		//���n����
		/*if (pos.p.y >= GROUND_Y2 - pos.hl.y) {
			m_bJump = false;
			m_velocity.y = 0.0f;
		}
		else {
			m_bJump = true;
		}*/

		//X��
		pos.p.x = max(axis_min + pos.hl.x, pos.p.x);
		pos.p.x = min(pos.p.x, axis_max - pos.hl.x);

		//Y��
		pos.p.y = max(m_Ground + pos.hl.y, pos.p.y);
		pos.p.y = min(pos.p.y, SCREEN_HEIGHT - pos.hl.y);

		//���n����
		if (pos.p.y <= m_Ground + pos.hl.y) {
			m_bJump = false;
			m_velocity.y = 0.0f;
		}
		else {
			m_bJump = true;
		}
		//*****************************************************************�M�����Ƃ���*****************************************************************************************
		break;
	}

	//����
	m_velocity.x = m_velocity.x * VELOCITY_RESIST;

	//�ړ��x�N�g���̏�����
	m_vecDir.x = NULL;
	
	//���Ⴊ�݂̏�����
	m_Squats = false;

	//�K�i����
	if (m_Climb || m_hashiraue) {
		m_velocity.y = m_velocity.y * VELOCITY_RESIST;
		m_vecDir.y = NULL;
	}
	else {
		m_vecDir.y = GRAVITY;
	}

	if (pos.p.y < GROUND_Y2 || m_Climb) {
		m_Ground = GROUND_Y1;
	}
	else {
		m_Ground = GROUND_Y2;
	}

	return true;
}

//�`��
void CPlayer::Draw(void) {

	//�v���C���[�̕`��
	//ppDrawer->SetTexture(k_kobeni);
	//ppDrawer->Draw(pos.p, pos.hl, D3DCOLOR_RGBA(255, 255, 255, 255));
	
	//*****************************************************************�M�����Ƃ���*****************************************************************************************
	////���W������
	Sprite3D::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y), pos.hl.x, pos.hl.y);


	////�`��
	//LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();
	//Sprite3D::Draw(pDevice, DirectX3DGetTEXTURE(k_kobeni));
	Sprite3D::Draw(k_kobeni , pos , -1.0f);
	//*****************************************************************�M�����Ƃ���*****************************************************************************************
}

//���ړ� : (false �E : true ��)
void CPlayer::SetVelocityX(bool direction) {

	if (direction) {
		m_vecDir.x += VECDIR_X;
	}
	else {
		m_vecDir.x -= VECDIR_X;
	}
}

//�c�ړ� : (false �� : true ��)
void CPlayer::SetVelocityY(bool direction) {

	if (direction) {
		m_vecDir.y += VECDIR_X;
	}
	else {
		m_vecDir.y -= VECDIR_X;
	}
}

//�W�����v
void CPlayer::Jump(void) {

	//�W�����v���łȂ��Ȃ�W�����v
	if (!m_bJump) {

		//�t���O���W�����v���ɕύX
		m_bJump = true;

		//�����x�ɃW�����v�͂�ݒ�
		m_velocity.y = JUMP_VALUE;

	}
}


//*****************************************************************************
// �ړ��ł���͈͂��Ƃ�
//*****************************************************************************
void CPlayer::SetMoveRange(RECT view_range) {
	axis_max = view_range.right;
	axis_min = view_range.left;
}

//*****************************************************************************
// �K�i��o��ݒ�
//*****************************************************************************
void CPlayer::SetClimb(bool climbing) {
	m_Climb = climbing;
}

//*****************************************************************************
// �o���FLAG�����
//*****************************************************************************
bool CPlayer::GetClimb(void) {
	return m_Climb;
}

//*****************************************************************************
// ���Ⴊ��
//*****************************************************************************
void CPlayer::Squats(void) {
	if (!m_Squats) {
		m_Squats = true;
	}
}

//*****************************************************************************
// �ʒu�ݒ�X
//*****************************************************************************
void CPlayer::SetPosX(float position) {
	pos.p.x = position;
}
//*****************************************************************************
// �ʒu�ݒ�Y
//*****************************************************************************
void CPlayer::SetPosY(float position) {
	pos.p.y = position;
}
//*****************************************************************************
// ����G�Ă��邩�̔���
//*****************************************************************************
void CPlayer::SetHashira(bool sw) {
	m_hashiraue = sw;
}