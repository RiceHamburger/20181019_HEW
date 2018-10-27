//=====================================================================//
//		�`���[�g���A�� [TutorialMap.cpp]                               //
//                                                                     //
//                                               SoSei				   //
//                                               2018/10/06            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "TutorialMap.h"
#include "DirectX3D.h"
#include "Texture.h"
#include "Config.h"

//=====================================================================//
//                                                                     //
//                       �O���[�o���ϐ��錾						       //
//                                                                     //
//=====================================================================//
static bool g_tutorialClear = false;
static CTutorialMap* g_pTutorialMap = NULL;
static float g_mapUNum = 0;
/* --------------------------------
�`���[�g���A���̏�������
-------------------------------- */
void TutorialInit(void)
{
	g_pTutorialMap = new CTutorialMap;
}
/* --------------------------------
�`���[�g���A���̏I������
-------------------------------- */
void TutorialUnit(void)
{
	PTR_DELETE(g_pTutorialMap);
}
/* --------------------------------
�`���[�g���A���̕`�揈��
-------------------------------- */
void TutorialDraw(void)
{
	g_pTutorialMap->CDraw();
}
/* --------------------------------
�`���[�g���A���̍X�V����
-------------------------------- */
void TutorialUpdate(void)
{
	if (g_mapUNum > 1.225)
	{
		g_tutorialClear = true;
		return;
	}
	g_mapUNum += 0.0025f;
	g_pTutorialMap->SetUVNum(g_mapUNum, 0);
}

/* --------------------------------
�N���A�\
-------------------------------- */
bool TutorialClear(void)
{
	return g_tutorialClear;
}


//******************************   �`���[�g���A���p�N���X�ݒ�   ******************************//
CTutorialMap::CTutorialMap()
{
	//������
	SetPos(D3DXVECTOR2(400.0f, 450.0f), 1600, 900);
	SetDivide(2, 1);
	SetUVNum(0, 0);
	m_pDevice = DirectX3DGetDevice();
	m_pTex = DirectX3DGetTEXTURE(k_tutorialMap);
}
CTutorialMap::~CTutorialMap()
{
	m_pTex->Release();
	m_pTex = NULL;
	m_pDevice = NULL;
}
void CTutorialMap::CDraw(void)
{
	Draw(m_pDevice, m_pTex);
}