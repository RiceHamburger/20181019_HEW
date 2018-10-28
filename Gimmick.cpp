//=============================================================================
//
// ギミッククラス [Gimmick.cpp]
//										Autor:ロ
//										Date:2018/10/26
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "DirectX3D.h"
#include "Gimmick.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Gimmick::Gimmick(k_Texture index, Float2 Pos, Float2 hl) : CPillar(index, Pos, hl)
{
	
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Gimmick::~Gimmick()
{

}

RectC2D Gimmick::GetPosition(void) {
	return pos;
}