#include "cameraManager.h"
#include "camera.h"

static Camera *camera;

//*****************************************************************************
// �J�����̏�������
//*****************************************************************************
void CameraManager_Initialize(void) {
	camera = new Camera();
}

//*****************************************************************************
// �J�����̏I������
//*****************************************************************************
void CameraManager_Finalize(void) {
	if (camera) { delete camera; camera = NULL; }
}

//*****************************************************************************
// �J�����̍X�V����
//*****************************************************************************
void CameraManager_Update(D3DXVECTOR2 player1_vec, D3DXVECTOR2 player2_vec) {
	camera->Update(player1_vec, player2_vec);
}

//*****************************************************************************
// �J�����̐ݒ�X�V
//*****************************************************************************
void CameraManager_Draw(void) {
	camera->SetTransform();
}

//*****************************************************************************
// �Q�b�g�J�����̃r���[�͈�
//*****************************************************************************
RECT GetCaneraRange(void) {
	return camera->GetViewRange();
}