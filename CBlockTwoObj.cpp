//=====================================================================//
//		�u���b�N�Q�I�u�W�F�N���X [CBlockTwoObj.cpp]                    //
//                                                                     //
//                                               GP52A275 SoSei        //
//                                               2018/10/28            //
//---------------------------------------------------------------------//
//   2018/10/28�@                                                      //
//   Sprite3D���p���A�p�x�v�Z�̕`�����ꂽ							   //
//                                                                     //
//                                                                     //
//=====================================================================//
#include "CBlockTwoObj.h"
#include "Config.h"

#define ROTATE_ZERO	(0)			//�@�p�x�O
#define ROTATE_INIT	(60.0f)		//�@�����̊p�x
#define ROTATE_MOVE_VALUE	(0.25f)		//�@�p�x�ړ��̗�
#define ROTATE_OBJ_Y_MOVE_VALUE (0.5f)	//�@�I�u�W�F�ړ��̗�
#define ROTATE_OBJ_X_MOVE_VALUE (0.35f)	//�@�I�u�W�F�ړ��̗�
#define ROTATE_G	(1.25f)	//�@�I�u�W�F�ړ��̌���


CBlockTwoObj* g_pPaint = NULL;	//�@�G�̃|�C���^�[
CBlockTwoObj* g_pBridge = NULL;	//�@���̃|�C���^�[

float g_rotate = ROTATE_INIT;	//�@���L�p�x
float g_BridgeYMove = ROTATE_ZERO;	//�@���ړ���
float g_BridgeXMove = ROTATE_ZERO;	//�@���ړ���
/* --------------------------------
�u���b�N�Q�I�u�W�F�̏�������
-------------------------------- */
void BlockTwoObjInit(void)
{
	g_pPaint = new CBlockTwoObj(E_PAINT);
	g_pBridge = new CBlockTwoObj(E_BRIDGE);
}			  
/* --------------------------------
�u���b�N�Q�I�u�W�F�̏I������
-------------------------------- */
void BlockTwoObjUnit(void)
{
	PTR_DELETE(g_pPaint);
	PTR_DELETE(g_pBridge);
}
/* --------------------------------
�u���b�N�Q�I�u�W�F�̕`�揈��
-------------------------------- */
void BlockTwoObjDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();

	// �G�Ƌ���`��
	g_pPaint->DrawRotate(pDevice, DirectX3DGetTEXTURE(k_kobeni), D3DXToRadian(g_rotate));
	g_pBridge->DrawRotate(pDevice, DirectX3DGetTEXTURE(k_kobeni), D3DXToRadian(g_rotate));
}

/* --------------------------------
�u���b�N�Q�I�u�W�F�̍X�V����
-------------------------------- */
void BlockTwoObjUpdate(void)
{
	// �������ɂȂ��Ă��邩
	if (g_rotate > ROTATE_ZERO)
	{
		//�@��]�v�Z
		g_rotate -= ROTATE_MOVE_VALUE;
		g_BridgeYMove -= ROTATE_OBJ_Y_MOVE_VALUE;
		g_BridgeXMove += ROTATE_OBJ_X_MOVE_VALUE;
		// XY�ړ��̃��Z�b�g�@�T�C�Y���̂܂�
		g_pBridge->SetPos(D3DXVECTOR2(1150.0f + g_BridgeXMove, 620.0f + g_BridgeYMove * ROTATE_G), 220, 20);
	}
	// ���������Œ�
	else if (g_rotate <= ROTATE_ZERO)
	{
		g_rotate = ROTATE_ZERO;
	}
}

/* --------------------------------
�u���b�N�Q�ʉ߉\��
-------------------------------- */
BOOL TrueIsBlockTwoObjOver(void)
{
	if (g_rotate == ROTATE_ZERO)
		return TRUE;
}


/* --------------------------------
�u���b�N�Q�I�u�W�F�̃N���X
-------------------------------- */
CBlockTwoObj::CBlockTwoObj(E_BlockTwoObj objEnum) 
	: E_ObjType(objEnum)
{
	switch (E_ObjType)
	{
	case E_PAINT:
		SetPos(D3DXVECTOR2(1000.0f, 225.0f), 100, 100);
		SetDivide(1, 1);
		SetUVNum(0, 0);
		break;
	case E_BRIDGE:
		SetPos(D3DXVECTOR2(1150.0f, 620.0f), 220, 20);
		SetDivide(1, 1);
		SetUVNum(0, 0);
		break;
	}
}
CBlockTwoObj::~CBlockTwoObj(){}