//=============================================================================
//
// ギミッククラス [Gimmick.h]
//										Autor:ロ
//										Date:2018/10/26
//=============================================================================

#ifndef GIMMICK_H
#define GIMMICK_H

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CPillar.h"

//*****************************************************************************
// ギミッククラス
//*****************************************************************************
class Gimmick : public CPillar {
private:
	
public:
	Gimmick(k_Texture index, Float2 Pos, Float2 hl);
	~Gimmick();

	RectC2D GetPosition(void);
};

#endif