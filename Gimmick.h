//=============================================================================
//
// �J�����N���X [camera.h]
//										Autor:��
//										Date:2018/09/30
//=============================================================================

#ifndef GIMMICK_H
#define GIMMICK_H

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <d3dx9.h>


//*****************************************************************************
// �J�����N���X
//*****************************************************************************
class Camera {
private:
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	D3DXVECTOR2 pos;
	RECT view_range;

	//player ui width
	int UI_Width;
public:
	Camera();
	~Camera();

	void Update(D3DXVECTOR2 player1_vec, D3DXVECTOR2 player2_vec);
	void SetTransform();
	RECT GetViewRange();
};

#endif