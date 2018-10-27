//=====================================================================//
//		���͏��� [input.h]                                             //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/07/05            //
//   2018/08/03  ver2.0                                                //
//   �ǉ��R���g���[���p�b�h�@�\                                        //
//   2018/10/06  ver3.0                                                //
//   �R���g���[���p�b�h�����ǉ�                                        //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#ifndef INPUT_H_
#define INPUT_H_

#define DIRECTINPUT_VERSION (0x0800)
#include <Windows.h>
#include <dinput.h>
#include <Xinput.h>
//#pragma comment (lib ,"dinput8.dll")
#pragma comment (lib, "xinput.lib")

/**************************************************

�萔��`

**************************************************/
#define PAD_VIBRATION_TIME	(250)	//PAD�R���g���[���̐U������

/**************************************************

PAD�R���g���[���\����

**************************************************/
typedef struct s_controlerState_tag
{
	XINPUT_STATE state;			//PAD�R���g���[���̏��
	bool bConnected;			//�ڑ�����Ă�����
}s_controlerState;

/**************************************************

�v���g�^�C�v�錾

**************************************************/

/* --------------------------------
�L�[�{�[�h����������
-------------------------------- */
bool KeyboardInitialize(HINSTANCE hInstance, HWND hWnd);
/* --------------------------------
�L�[�{�[�h�I������
-------------------------------- */
void KeyboardFinalize(void);
/* --------------------------------
�L�[�{�[�h�X�V����
-------------------------------- */
void KeyboardUpdate(void);
/* --------------------------------
DIK_�L�[�֘A����
-------------------------------- */
bool KeyboardIsPress(int nKey);
bool KeyboardIsTrigger(int nKey);
bool KeyboardIsRelease(int nKey);
/* --------------------------------
PAD�R���g���[������������
-------------------------------- */
void PadInitialize(void);
/* --------------------------------
PAD�R���g���[���X�V����
-------------------------------- */
void PadStateUpdate(void);
/* --------------------------------
PAD�R���g���[���I������
-------------------------------- */
void PadStateFinalize(void);
/* --------------------------------
PAD�U�������֘A
-------------------------------- */
void SetPadVibration(int uesrNum, bool bIs);
void StopPadVibration(int uesrNum);
bool GetPadVibration(void);
/* --------------------------------
�L�[�̓��͏���
-------------------------------- */
void ReadInput(void);
#endif