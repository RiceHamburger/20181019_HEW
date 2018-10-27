//=====================================================================//
//		�f�o�C�X���� [directX3D.cpp]								   //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/05/15            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "DirectX3D.h"
#include "Config.h"

//=====================================================================//
//                                                                     //
//                       �O���[�o���ϐ��錾						       //
//                                                                     //
//=====================================================================//
static LPDIRECT3D9 g_pD3D = NULL;				//Direct3 �C���^�t�F�[�X
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Device9 �f�o�C�X��ID
static LPDIRECT3DTEXTURE9 g_pTexture = NULL;	//�e�N�X�`���ۑ��ꏊ

//=====================================================================//
//                                                                     //
//                       ����:hWnd....�E�B���h�E�n���h��		       //
//                                                                     //
//=====================================================================//
bool DirectX3DInitialize(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//DX9�̃f�C�p�X���擾
	D3DPRESENT_PARAMETERS g_d3dpp = {};			//�f�o�C�X�̓����ݒ肷��\����
	g_d3dpp.BackBufferWidth = SCREEN_WIDTH;
	g_d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.BackBufferCount = 1;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�X���b�v�@�G�t�F�N�g
	g_d3dpp.Windowed = TRUE;					//!!�t���[�X�N���[���͂������C��!!
	g_d3dpp.EnableAutoDepthStencil = TRUE;		//3D���ɑO�ƌ��̔���
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//D24S8 Depth�o�b�t�@16�r�b�g�m�ۂ���

	//�t���[�X�N���[������Ȃ����Ӗ����Ȃ�
	//���j�^�[�ɑΉ�����Hz�����Ȃ��ƃ_��
	g_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	HRESULT hr = g_pD3D->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&g_d3dpp,
		&g_pD3DDevice
	);
	if (FAILED(hr))
	{
		hr = g_pD3D->CreateDevice
		(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&g_d3dpp,
			&g_pD3DDevice
		);
		if (FAILED(hr))
		{
			hr = g_pD3D->CreateDevice
			(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&g_d3dpp,
				&g_pD3DDevice
			);
		}
		if (FAILED(hr))
		{
			//�擾���s
			MessageBox(NULL, FAILED_MESSAGE, FAILED_MESSAGE_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_DEFBUTTON1);
		}
		if (FAILED(hr))
		{
			return false;
		}


	}
	//���T���v���[
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//�c�T���v���[
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	////�g��
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	//�k��
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	//�~�b�v�}�b�v
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	//�A���t�@�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//�|���S���̃A���t�@�ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	return true;
}

//=====================================================================//
//                                                                     //
//							    �I������						       //
//                                                                     //
//=====================================================================//
void DirectX3DFinalize(void)
{
	/* --------------------------------
	�f�o�C�X�J��
	-------------------------------- */
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	/* --------------------------------
	DX�J��
	-------------------------------- */
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=====================================================================//
//                                                                     //
//						D3D�f�o�C�X�|�C���^�[�̎擾				       //
//                                                                     //
//=====================================================================//
LPDIRECT3DDEVICE9 DirectX3DGetDevice(void)
{
	/* --------------------------------
	���^�[���f�o�C�X
	-------------------------------- */
	return g_pD3DDevice;
}

//=====================================================================//
//                                                                     //
//							�e�N�X�`���̎擾					       //
//                                                                     //
//=====================================================================//
LPDIRECT3DTEXTURE9 DirectX3DGetTEXTURE(HWND hWnd, LPCSTR address)
{
	/* --------------------------------
	���^�[���e�N�X�`��
	-------------------------------- */
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, address, &g_pTexture)))
	{
		MessageBox(hWnd, "�e�N�X�`���t�@�C���ǂݍ��ݎ��s", FAILED_MESSAGE_TITLE, MB_OKCANCEL | MB_DEFBUTTON2);
	}
	return g_pTexture;
}

//=====================================================================//
//                                                                     //
//                          �����_�[�ύX�p                             //
//                                                                     //
//=====================================================================//
// �����_�[�X�e�[�g�̕ύX
void SetRenderState(k_RENDER_STATE RenderState)
{
	/* --------------------------------
	�����_�����O�w��p
	-------------------------------- */
	switch (RenderState)
	{
	/* --------------------------------
	�����_�����O�@�f�t�H���g
	-------------------------------- */
	case k_RENDER_DEFAULT:
	{
		// �s�����I�u�W�F�N�g
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);			//�A���t�@�u�����f�B���O�̖�����
	}
	break;
	/* --------------------------------
	�����_�����O�@����
	-------------------------------- */
	case k_RENDER_ALPHATEST:
	{
		// ���e�X�g�ɂ�铧���̈�̐؂蔲��
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//�u�����f�B���O�I�v�V�������Z
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
	}
	break;
	/* --------------------------------
	�����_�����O�@�����Z
	-------------------------------- */
	case k_RENDER_HALFADD:
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//�A���t�@�u�����f�B���O�̗L����
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				//Z�o�b�t�@�ւ̏������݂𖳌��ɂ���B
		
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//�u�����f�B���O�I�v�V�������Z
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//SRC�̐ݒ�
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DEST�̐ݒ�

	}
	break;
	/* --------------------------------
	�����_�����O�@�t���[���Z����
	-------------------------------- */
	case k_RENDER_ADD:
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//�A���t�@�u�����f�B���O�̗L����
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//�u�����f�B���O�I�v�V�������Z
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);			//SRC�̐ݒ�
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DEST�̐ݒ�
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//�A���t�@�e�X�g�̖�����
	}
	break;
	}
}