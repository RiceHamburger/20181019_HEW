//=====================================================================//
//		�e�N�X�`������ [texture.cpp]                                   //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/07/05            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "Texture.h"


//=====================================================================//
//                                                                     //
//                           �e�N�X�`��							       //
//                                                                     //
//=====================================================================//
static const textureData textureFiles[] =
{
	{ "asset/texture/title.jpg",				1000,	800	},		// index�̂��߁@�g��Ȃ�
	{ "asset/texture/title.jpg",				1000,	800 },		// �^�C�g��
	{ "asset/texture/kobeni.png",				512,	512 },		// kobeni
	{ "asset/texture/sozai1.jpg",				3200,	900},		// �^�C�g��
	{ "asset/texture/heart.png",				32,		32 },		// ������
	{ "asset/texture/playerLifeBG.jpg",			70,		900 },		// �����͂̔w�i
	{ "asset/texture/ladder.jpg",				77,		431 },		// �͂���
	{ "asset/texture/TimeNum.png",				320,	42 },		// �����L���O�p�i���o�[
	{ "asset/texture/ranking.png",				1600,	900 },		// �����L���O
}; 

/* --------------------------------

�z��T�C�Y�̌v��ƌ������o�� ARRAYSIZE����������
static const int TEXTURE_NUM_MAX = sizeof(textureFiles) / sizeof(textureFiles[0]);

-------------------------------- */
static const int TEXTURE_NUM_MAX = ARRAYSIZE(textureFiles);
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_NUM_MAX];

//=====================================================================//
//                                                                     //
//						�e�N�X�`���ǂݍ��݊֐�					       //
//                                                                     //
//=====================================================================//
int TextrueInit(void)
{
	/* --------------------------------
	�f�o�C�X�ȂǃQ�b�g
	-------------------------------- */
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = DirectX3DGetDevice();
	/* --------------------------------
	�ǂݍ��ݎ��s��
	-------------------------------- */
	int failedCount = 0;

	for (int i = 0; i < TEXTURE_NUM_MAX; i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, textureFiles[i].textureName, &g_pTextures[i]);
		if (FAILED(hr))
		{
			/* --------------------------------
			�ǂ߂Ȃ�������
			-------------------------------- */
			failedCount++;
		}
	}
	/* --------------------------------
	���^�[���ǂ߂Ȃ�������
	-------------------------------- */
	return failedCount;
}

//=====================================================================//
//                                                                     //
//						�e�N�X�`���̏I�������֐�				       //
//                                                                     //
//=====================================================================//
void TextrueUnit(void)
{
	/* --------------------------------
	�e�N�X�`���̊J��
	-------------------------------- */
	for (int i = 0; i < TEXTURE_NUM_MAX; i++)
	{
		if (g_pTextures[i] != NULL)
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}
//=====================================================================//
//                                                                     //
//						�Q�b�g�e�N�X�`���̕`��֐�				       //
//                                                                     //
//=====================================================================//
LPDIRECT3DTEXTURE9 DirectX3DGetTEXTURE(int index)
{
	/* --------------------------------
	���^�[���w�肵���e�N�X�`��
	-------------------------------- */
	return g_pTextures[index];
}
int TextrueGetWidth(int index)
{
	/* --------------------------------
	���^�[���w�肵���e�N�X�`����
	-------------------------------- */
	return textureFiles[index].width;
}
int TextrueGetHeight(int index)
{
	/* --------------------------------
	���^�[���w�肵���e�N�X�`������
	-------------------------------- */
	return textureFiles[index].height;
}