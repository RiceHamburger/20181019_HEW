//=====================================================================//
//		�f�o�C�X���� [directX3D.h]								       //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/05/15            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#ifndef DIRECTX3D_H
#define DIRECTX3D_H

#include <Windows.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


/**************************************************

�����_�����O�penum

**************************************************/
typedef enum k_RENDER_STATE_tag
{
	k_RENDER_INDEX,			// �C���f�b�N�X
	k_RENDER_DEFAULT,		// �f�t�H���g(�s����)
	k_RENDER_ALPHATEST,		// ���e�X�g
	k_RENDER_HALFADD,		// �����Z����
	k_RENDER_ADD,			// ���Z����
	k_RENDER_MAX,			// �C���f�b�N�X�}�b�N�X
}k_RENDER_STATE;

/**************************************************

�v���g�^�C�v�錾

**************************************************/

/* --------------------------------
D3D�f�o�C�X����������
�߂�l:�������Ɏ��s������FALSE
����:hWnd....�E�B���h�E�n���h��
-------------------------------- */
bool DirectX3DInitialize(HWND hWnd);
/* --------------------------------
D3D�f�o�C�X�I������
-------------------------------- */
void DirectX3DFinalize(void);
/* --------------------------------
D3D�f�o�C�X�|�C���^�[�̎擾
-------------------------------- */
LPDIRECT3DDEVICE9 DirectX3DGetDevice(void);
/* --------------------------------
�e�N�X�`���̎擾
-------------------------------- */
LPDIRECT3DTEXTURE9 DirectX3DGetTEXTURE(HWND hWnd, LPCSTR address);

void SetRenderState(k_RENDER_STATE RenderState);

#endif //DIRECTX3D_H