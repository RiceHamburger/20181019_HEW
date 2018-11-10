/*====================================================================================

��N���X�@ [CDoor.cpp]
Autor	: ���E�r�����`����
Date	: 2018/10/26
--------------------------------------------------------------------------------------
�R�����g:
��N���X : �w�i

--------------------------------------------------------------------------------------
�C������:
====================================================================================*/


/*--------------------------------------------------------------------------------------
�C���N���[�h�t�@�C��
--------------------------------------------------------------------------------------*/
#include "CDoor.h"
#include "PlayerManager.h"
/*--------------------------------------------------------------------------------------
�񋓌^ : �\����
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
�}�N����`
--------------------------------------------------------------------------------------*/
#define DOORCOUNT (2)											//�h�A�[��
#define DOORCOLORTIME (5)										//���ԑ���
#define DOORCOLOR (D3DCOLOR_RGBA(255, 100, 200, 255))			//�ς���F
#define DOORCOLOR_WHITE (D3DCOLOR_RGBA(255, 255, 255, 255))		//���F
#define DOOR_WIDTH (100)
#define DOOR_HEIGHT (100)

/*--------------------------------------------------------------------------------------
�N���X�錾
--------------------------------------------------------------------------------------*/

//�e�N�X�`���A��h�A�[�ʒu�A���h�A�[�ʒu
CDoor::CDoor(k_Texture index, D3DXVECTOR2 pos0, D3DXVECTOR2 pos1)
{
	m_TextureIndex = index;

	m_pos[PLAYER_ONE] = pos0;
	m_pos[PLAYER_TWO] = pos1;
	
	m_color[PLAYER_ONE] = DOORCOLOR;
	m_color[PLAYER_TWO] = DOORCOLOR;

	m_OnOff[PLAYER_ONE] = false;
	m_OnOff[PLAYER_TWO] = false;
	m_OK = false;

	Sprite3D::SetColor(DOORCOLOR_WHITE);
	Sprite3D::SetDivide(1, 1);
	Sprite3D::SetUVNum(0, 0);
}

CDoor::CDoor(k_Texture index)
{
	m_TextureIndex = index;
	
	m_pos[PLAYER_ONE] = D3DXVECTOR2(3015.0f, 120.0f);
	m_pos[PLAYER_TWO] = D3DXVECTOR2(3015.0f, 570.0f);

	m_color[PLAYER_ONE] = DOORCOLOR;
	m_color[PLAYER_TWO] = DOORCOLOR;

	m_OnOff[PLAYER_ONE] = false;
	m_OnOff[PLAYER_TWO] = false;
	m_OK = false;

	Sprite3D::SetColor(DOORCOLOR_WHITE);
	Sprite3D::SetDivide(1, 1);
	Sprite3D::SetUVNum(0, 0);
}

CDoor::~CDoor()
{

}

//�h�A�[�������ꂽ�����f(���œ��蔻�����Ă�)
void CDoor::Switch(int index)
{
	switch (index)
	{
	case PLAYER_TWO:
		//���蔻��
		if (GetPlayerPos(PLAYER_TWO).y <= m_pos[PLAYER_ONE].y + DOOR_HEIGHT &&
			GetPlayerPos(PLAYER_TWO).y >= m_pos[PLAYER_ONE].y - DOOR_HEIGHT) {
			if (GetPlayerPos(PLAYER_TWO).x <= m_pos[PLAYER_ONE].x + DOOR_WIDTH &&
				GetPlayerPos(PLAYER_TWO).x >= m_pos[PLAYER_ONE].x - DOOR_WIDTH) {
				//On�ɂȂ�������
				m_OnOff[PLAYER_ONE] = true;

				if (m_OnOff[PLAYER_ONE]) {
					if (m_OnOff[PLAYER_TWO]) {
						//����������Ă���Ƃ���
						m_OK = true;
					}
				}
			}
			//���Ԃ�����
			start[PLAYER_ONE] = clock();
			}

		break;

	case PLAYER_ONE:
		//���蔻��
		if (GetPlayerPos(PLAYER_ONE).y <= m_pos[PLAYER_TWO].y + DOOR_HEIGHT &&
			GetPlayerPos(PLAYER_ONE).y >= m_pos[PLAYER_TWO].y - DOOR_HEIGHT) {
			if (GetPlayerPos(PLAYER_ONE).x <= m_pos[PLAYER_TWO].x + DOOR_WIDTH &&
				GetPlayerPos(PLAYER_ONE).x >= m_pos[PLAYER_TWO].x - DOOR_WIDTH) {
				//On�ɂȂ�������
				m_OnOff[PLAYER_TWO] = true;

				if (m_OnOff[PLAYER_TWO]) {
					if (m_OnOff[PLAYER_ONE]) {
						//����������Ă���Ƃ���
						m_OK = true;
					}
				}
			}
			//���Ԃ�����
			start[PLAYER_TWO] = clock();
		}

		break;

	default:
		break;
	}
}

void CDoor::Draw(void)
{
	for (int i = 0; i < DOORCOUNT; i++) {

		Sprite3D::SetPos(m_pos[i], DOOR_WIDTH, DOOR_HEIGHT);	//�h�A�[�̈ʒu��`���x�����

		if (m_OnOff[i]) {										//�h�A�[���I����������w��F
			Sprite3D::SetColor(m_color[i]);
		}
		else {													//�I�t�������甒
			Sprite3D::SetColor(DOORCOLOR_WHITE);
		}

		Sprite3D::Draw(m_TextureIndex);

	}
}

//�h�A�[�������ꂽ���̎��ԂŐF�ς��̎��Ԃ����߂Ă�
void CDoor::ColorUpdate(void)
{
	for (int i = 0; i < DOORCOUNT; i++) {
		if (m_OnOff[i]) {
			end[i] = clock();
			if (((end[i] - start[i]) / 1000) >= DOORCOLORTIME) {
				//DOORCOLORTIME�̎��Ԉȏ�ɂȂ�ƃI�t�ɖ߂�
				m_OnOff[i] = false;
			}
		}
	}
}

//���������ꂽ��true�ɂȂ�
bool CDoor::Fin(void)
{
	return m_OK;
}