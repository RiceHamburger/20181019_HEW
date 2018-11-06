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
#include "Input.h"
#include "GameStage.h"
#include "CPlayer.h"
#include "PlayerManager.h"
#include "Gimmick_Manager.h"
#include "DoorManager.h"
#include "BlockTwoLoop.h"

//=====================================================================//
//                                                                     //
//							 �萔��`						           //
//                                                                     //
//=====================================================================//
#define	NUM_KEY_MAX						(256)					// �L�[�̍ő吔

#define VALUE_ZERO						(0)						// �ړ��ʁA�U���ʃ[��
#define VALUE_MAX						(65535)					// �ړ��ʁA�U���ʍő�l

#define MAX_CONTROLLERS					(4)						// XInput���F���ł���̂�4�܂�
#define CONTROLLER_USER_1				(0)						// �R���g���[�����[�U�[ �P
#define CONTROLLER_USER_2				(1)						// �R���g���[�����[�U�[ 2
#define THRESHOLD						(65536 / 4)				// PAD�A�i���O�{�^���̂������l
#define THRESHOLD_TRIGGER				(255 / 2)				// PAD�A�i���O�{�^���̂������l														   

//=====================================================================//
//                                                                     //
//							�v���g�^�C�v�錾						   //
//                                                                     //
//=====================================================================//
static bool initialize(HINSTANCE hInstance);					//DXinput�AXinput�̏�������
static void finalize(void);										//DXinput�AXinput�̏I������

//=====================================================================//
//                                                                     //
//							�O���[�o���ϐ�							   //
//                                                                     //
//=====================================================================//
static LPDIRECTINPUT8		g_pInput = NULL;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
static LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
static BYTE					g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
static BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
static BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N

static s_controlerState		GAME_PAD[MAX_CONTROLLERS];			// XInput PAD�\����
static WORD					g_buttons;							// PAD�̓��͏�񃏁[�N
static XINPUT_VIBRATION		g_vibration[MAX_CONTROLLERS];		// PAD�̐U����񃏁[�N
static bool					g_xinputVibrationCheck[MAX_CONTROLLERS] = { false };		// PAD�̐U�����
																
//=====================================================================//
//                                                                     //
//							���͏����̏�����						   //
//                                                                     //
//=====================================================================//
bool initialize(HINSTANCE hInstance)
{
	/* --------------------------------
	DXinput�V�K�쐬
	-------------------------------- */
	if (g_pInput == NULL)
	{
		/* --------------------------------
		DirectInput�I�u�W�F�N�g�̍쐬
		-------------------------------- */
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) {
			return false;
		}
	}
	/* --------------------------------
	Xinput PAD�R���g���[��������
	-------------------------------- */
	PadInitialize();

	return true;
}

//=====================================================================//
//                                                                     //
//							���͏����̏I������						   //
//                                                                     //
//=====================================================================//
void finalize(void)
{
	/* --------------------------------
	Xinput PAD�R���g���[����~�i�U���Ȃǁj
	-------------------------------- */
	PadStateFinalize();
	/* --------------------------------
	DXinput ���������
	-------------------------------- */
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=====================================================================//
//                                                                     //
//							�L�[�{�[�h�̏�����						   //
//                                                                     //
//=====================================================================//
bool KeyboardInitialize(HINSTANCE hInstance, HWND hWnd)
{
	/* --------------------------------
	���͏����̏�����
	-------------------------------- */
	if (!initialize(hInstance))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}
	/* --------------------------------
	�f�o�C�X�̍쐬
	-------------------------------- */
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}
	/* --------------------------------
	�f�[�^�t�H�[�}�b�g��ݒ�
	-------------------------------- */
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}
	/* --------------------------------
	�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	-------------------------------- */
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_EXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}
	/* --------------------------------
	�L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	-------------------------------- */
	g_pDevKeyboard->Acquire();

	/* --------------------------------
	�ݒ芮������ƃ��^�[��true
	-------------------------------- */
	return true;
}

//=====================================================================//
//                                                                     //
//						�L�[�{�[�h�̏I������						   //
//                                                                     //
//=====================================================================//
void KeyboardFinalize(void)
{
	/* --------------------------------
	���̓f�o�C�X(�L�[�{�[�h)�̃������J��
	�L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
	�������J��
	-------------------------------- */
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	/* --------------------------------
	���͏����̏I������
	-------------------------------- */
	finalize();
}

//=====================================================================//
//                                                                     //
//						�L�[�{�[�h�̍X�V����						   //
//                                                                     //
//=====================================================================//
void KeyboardUpdate(void)
{
	/* --------------------------------
	�L�[�̃o�b�t�@�[
	-------------------------------- */
	BYTE aKeyState[NUM_KEY_MAX];

	/* --------------------------------
	�f�o�C�X����f�[�^���擾
	-------------------------------- */
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		// aKeyState[DIK_SPACE] & 0x80 �L�^�p
		/* --------------------------------
		���[�v����
		-------------------------------- */
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			/* --------------------------------
			�L�[�g���K�[�E�����[�X���𐶐�
			-------------------------------- */
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];

			/* --------------------------------
			�L�[�v���X����ۑ�
			-------------------------------- */
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		/* --------------------------------
		�L�[�{�[�h�ւ̃A�N�Z�X�����擾
		-------------------------------- */
		g_pDevKeyboard->Acquire();
	}

	/* --------------------------------
	���ړ�	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_LEFT) || KeyboardIsPress(DIK_A))
	{
		SetPlayerMove(PLAYER_ONE , false);
	}
	/* --------------------------------
	�E�ړ�	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_RIGHT) || KeyboardIsPress(DIK_D))
	{
		SetPlayerMove(PLAYER_ONE , true);
	}
	/* --------------------------------
	��ړ�	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_UP) || KeyboardIsPress(DIK_W))
	{
		if (GetPlayerClimb(PLAYER_ONE)) {
			SetPlayerMoveY(PLAYER_ONE, true);
		}
	}
	/* --------------------------------
	���ړ�	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_DOWN) || KeyboardIsPress(DIK_S))
	{
		if (GetPlayerClimb(PLAYER_ONE)) {
			SetPlayerMoveY(PLAYER_ONE, false);
		}
	}
	/* --------------------------------
	�X�y�[�X�L�[	Player1
	-------------------------------- */
	if (KeyboardIsPress(DIK_SPACE))
	{
		SetPlayerJump(PLAYER_ONE);
	}
	/* --------------------------------
	���ړ�	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_J))
	{
		SetPlayerMove(PLAYER_TWO , false);
	}

	/* --------------------------------
	�E�ړ�	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_L))
	{
		SetPlayerMove(PLAYER_TWO , true);
	}
	/* --------------------------------
	��ړ�	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_I))
	{
		if (GetPlayerClimb(PLAYER_TWO)) {
			SetPlayerMoveY(PLAYER_TWO, true);
		}
	}
	/* --------------------------------
	���ړ�	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_K))
	{
		if (GetPlayerClimb(PLAYER_TWO)) {
			SetPlayerMoveY(PLAYER_TWO, false);
		}
	}
	/* --------------------------------
	�W�����v	Player2
	-------------------------------- */
	if (KeyboardIsPress(DIK_M))
	{
		SetPlayerJump(PLAYER_TWO);
	}


	/* --------------------------------
	����P
	-------------------------------- */
	if (KeyboardIsPress(DIK_Z) || KeyboardIsPress(DIK_J))
	{
		Door_Switch(PLAYER_TWO);
	}
	/* --------------------------------
	����Q
	-------------------------------- */
	if (KeyboardIsRelease(DIK_X) || KeyboardIsRelease(DIK_K))
	{
		Door_Switch(PLAYER_ONE);
	}
	/* --------------------------------
	����SP
	-------------------------------- */
	if (KeyboardIsPress(DIK_SPACE) || KeyboardIsPress(DIK_L))
	{

	}
	/* --------------------------------
	�G���^�[�L�[
	-------------------------------- */
	if (KeyboardIsRelease(DIK_RETURN))
	{
		SetStartKey();
	}

	/* --------------------------------
	�A�N�V����1
	-------------------------------- */
	if (KeyboardIsPress(DIK_Z))
	{
		BlockTwoSwitch();
	}
}


//=====================================================================//
//                                                                     //
//					�L�[�{�[�h�̃v���X��Ԃ��擾					   //
//                                                                     //
//=====================================================================//
bool KeyboardIsPress(int nKey)
{
	/* --------------------------------
	���^�[���L�[���
	-------------------------------- */
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}


//=====================================================================//
//                                                                     //
//					�L�[�{�[�h�̃g���K�[��Ԃ��擾					   //
//                                                                     //
//=====================================================================//
bool KeyboardIsTrigger(int nKey)
{
	/* --------------------------------
	���^�[���L�[���
	-------------------------------- */
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=====================================================================//
//                                                                     //
//					�L�[�{�[�h�̃����|�X��Ԃ��擾					   //
//                                                                     //
//=====================================================================//
bool KeyboardIsRelease(int nKey)
{
	/* --------------------------------
	���^�[���L�[���
	-------------------------------- */
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//=====================================================================//
//                                                                     //
//						PAD�R���g���[���̏�����						   //
//                                                                     //
//=====================================================================//
void PadInitialize(void)
{


	/* --------------------------------
	PAD�R���g���[���ǂݍ���
	�ꎞ�p�ϐ��錾
	-------------------------------- */
	DWORD dwResult;

	/* --------------------------------
	�ڑ�����Ă���PAD���𒲂ׂ�
	-------------------------------- */
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		/* --------------------------------
		��Ԏ擾
		-------------------------------- */
		dwResult = XInputGetState(i, &GAME_PAD[i].state);

		/* --------------------------------
		�ڑ����Ă���
		-------------------------------- */
		if (dwResult == ERROR_SUCCESS)
		{
			GAME_PAD[i].bConnected = true;
			/* --------------------------------
			PAD�R���g���[���U��������
			-------------------------------- */
			g_xinputVibrationCheck[i] = false;
		}
		/* --------------------------------
		�ڑ����Ă��Ȃ�
		-------------------------------- */
		else
		{
			GAME_PAD[i].bConnected = false;
		}
	}
}

//=====================================================================//
//                                                                     //
//						PAD�R���g���[���̏I������					   //
//                                                                     //
//=====================================================================//
void PadStateFinalize(void)
{
	/* --------------------------------
	PAD�R���g���[���g�p��~
	-------------------------------- */
	XInputEnable(false);
}
//=====================================================================//
//                                                                     //
//						PAD���[�U�[�ʂ̍X�V����						   //
//                                                                     //
//=====================================================================//
void PadUserUpdate(int userNum)
{
	/* --------------------------------
	PAD�R���g���[����Ԏ擾
	�L�[�̏��擾
	-------------------------------- */
	XInputGetState(userNum, &GAME_PAD[userNum].state);
	g_buttons = GAME_PAD[userNum].state.Gamepad.wButtons;

	/* --------------------------------
	��
	-------------------------------- */
	if (GAME_PAD[userNum].state.Gamepad.sThumbLY >= THRESHOLD)
	{

	}
	/* --------------------------------
	��
	-------------------------------- */
	if (GAME_PAD[userNum].state.Gamepad.sThumbLY <= -THRESHOLD)
	{

	}
	/* --------------------------------
	��
	-------------------------------- */
	if (GAME_PAD[userNum].state.Gamepad.sThumbLX <= -THRESHOLD)
	{
		SetPlayerMove(userNum, false);
	}
	/* --------------------------------
	�E
	-------------------------------- */
	if (GAME_PAD[userNum].state.Gamepad.sThumbLX >= THRESHOLD)
	{
		SetPlayerMove(userNum, true);
	}
	/* --------------------------------
	�W�����v
	-------------------------------- */
	if (g_buttons & XINPUT_GAMEPAD_A)
	{
		SetPlayerJump(userNum);
	}

	/* --------------------------------
	�X�^�[�g�ڂ���
	-------------------------------- */
	if (g_buttons & XINPUT_GAMEPAD_START)
	{
		SetStartKey();
	}

}


//=====================================================================//
//                                                                     //
//						PAD�R���g���[���̍X�V����					   //
//                                                                     //
//=====================================================================//
void PadStateUpdate(void)
{
	PadUserUpdate(CONTROLLER_USER_1);
	PadUserUpdate(CONTROLLER_USER_2);
	/*
					**********     ���� �R�s�y�p     **********
	//�A�i���O�����L�[
	if (GAME_PAD[i].state.Gamepad.sThumbLY > Threshold)
	if (GAME_PAD[i].state.Gamepad.sThumbLY < -Threshold)
	if (GAME_PAD[i].state.Gamepad.sThumbLX > Threshold)
	if (GAME_PAD[i].state.Gamepad.sThumbLX < -Threshold)

	//�f�W�^�������L�[
	if (g_buttons & XINPUT_GAMEPAD_DPAD_UP)
	if (g_buttons & XINPUT_GAMEPAD_DPAD_DOWN)
	if (g_buttons & XINPUT_GAMEPAD_DPAD_LEFT)
	if (g_buttons & XINPUT_GAMEPAD_DPAD_RIGHT)

	//�e��{�^�� �󐧌�
	if (g_buttons & XINPUT_GAMEPAD_A);
	if (g_buttons & XINPUT_GAMEPAD_B);
	if (g_buttons & XINPUT_GAMEPAD_X);
	if (g_buttons & XINPUT_GAMEPAD_Y);
	if (g_buttons & XINPUT_GAMEPAD_START);
	if (g_buttons & XINPUT_GAMEPAD_BACK);
	if (g_buttons & XINPUT_GAMEPAD_LEFT_THUMB);//���A�i���O�����L�[���p�b�h���ɉ������ꍇ
	if (g_buttons & XINPUT_GAMEPAD_RIGHT_THUMB);//�E�A�i���O�����L�[���p�b�h���ɉ������ꍇ
	if (g_buttons & XINPUT_GAMEPAD_LEFT_SHOULDER);
	if (g_buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
	if (GAME_PAD[i].state.Gamepad.bLeftTrigger);
	if (GAME_PAD[i].state.Gamepad.bRightTrigger);

	//�U���Z�b�g
	XInputSetState(0, &g_vibration);
	*/
}

//=====================================================================//
//                                                                     //
//					�Z�b�gPAD�R���g���[���̐U�����					   //
//                                                                     //
//=====================================================================//
void SetPadVibration(int uesrNum, bool bIs)
{
	/* --------------------------------
	�U�����Ă��Ȃ��Ɓ@�U���Z�b�g
	-------------------------------- */
	if (!g_xinputVibrationCheck)
	{
		g_xinputVibrationCheck[uesrNum] = bIs;
		g_vibration[uesrNum].wLeftMotorSpeed = g_vibration[uesrNum].wRightMotorSpeed = VALUE_MAX;
		XInputSetState(uesrNum, &g_vibration[uesrNum]);
	}
}

//=====================================================================//
//                                                                     //
//					 ��~PAD�R���g���[���̐U�����					   //
//                                                                     //
//=====================================================================//
void StopPadVibration(int uesrNum)
{
	/* --------------------------------
	��~�U��
	-------------------------------- */
	SetPadVibration(uesrNum, true);
	g_xinputVibrationCheck[uesrNum] = false;
	g_vibration[uesrNum].wLeftMotorSpeed = g_vibration[uesrNum].wRightMotorSpeed = VALUE_ZERO;
	XInputSetState(uesrNum, &g_vibration[uesrNum]);
}
//=====================================================================//
//                                                                     //
//					�Q�b�gPAD�R���g���[���̐U�����					   //
//                                                                     //
//=====================================================================//
bool GetPadVibration(void)
{
	/* --------------------------------
	���^�[�����݂̐U�����
	-------------------------------- */
	if (g_xinputVibrationCheck[CONTROLLER_USER_1] && g_xinputVibrationCheck[CONTROLLER_USER_2])
		return true;
}


//=====================================================================//
//                                                                     //
//								input���s						       //
//                                                                     //
//=====================================================================//
void ReadInput(void)
{
	/* --------------------------------
	�L�[�{�[�h�̍X�V����
	-------------------------------- */
	KeyboardUpdate();
	PadStateUpdate();
}
