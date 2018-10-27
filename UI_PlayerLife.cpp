//=============================================================================
//
// �v���C���[�̐�����UI�N���X [UI_PlayerLife.h]
//										Autor:��
//										Date:2018/10/18
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "UI_PlayerLife.h"
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LIFE_POS_X	(35.0f)
//�����͂̍ő�l,�����l
#define PLAYER_LIFE_MAX (3)
//������UI�̍s��
#define LIFE_SPACE (20.0f)

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
UI_PlayerLife::UI_PlayerLife()
{
	//�ʒu�̐ݒ�
	pos.p.x = LIFE_POS_X;

	//�v���C���[������UI�̍������v�Z����
	pos.p.y = (TextrueGetHeight(k_tutorialMap) - (TextrueGetHeight(k_playerLife) * PLAYER_LIFE_MAX + LIFE_SPACE * (PLAYER_LIFE_MAX - 1)))/2;
	LifeHeight = TextrueGetHeight(k_playerLife);

	//�T�C�Y�̐ݒ�
	pos.hl.x = TextrueGetWidth(k_playerLife) / 2;
	pos.hl.y = LifeHeight / 2;

	//������
	//�iXY���W,����,�����j��ݒ�
	Sprite::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y), pos.hl.x, pos.hl.y);
	// �摜������
	Sprite::SetDivide(1, 1);
	// ����UV���W�ݒ�
	Sprite::SetUVNum(0, 0);
	
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
UI_PlayerLife::~UI_PlayerLife()
{

}

//*****************************************************************************
// �X�V
//*****************************************************************************
void UI_PlayerLife::Update() {

}

//*****************************************************************************
// �`��
//*****************************************************************************
void UI_PlayerLife::Draw()
{
	//�`��
	LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();

	//�w�i
	Sprite::SetPos(D3DXVECTOR2(0, 0), TextrueGetWidth(k_playerLifeBG), TextrueGetHeight(k_playerLifeBG));
	Sprite::Draw(pDevice, DirectX3DGetTEXTURE(k_playerLifeBG));

	for (int i = 0;i < PLAYER_LIFE_MAX;i++) {
		Sprite::SetPos(D3DXVECTOR2(pos.p.x, pos.p.y + (LifeHeight + LIFE_SPACE) * i), pos.hl.x, pos.hl.y);
		Sprite::Draw(pDevice, DirectX3DGetTEXTURE(k_playerLife));
	}
}