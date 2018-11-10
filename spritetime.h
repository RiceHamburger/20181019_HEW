#pragma once
//=============================================================================
//
// SpriteTIME [spritetime.h]
// Spritet_TimeRank用
//										Autor:Ryo
//										Date:2018/11/1
//=============================================================================
#ifndef SPRITETIME_H
#define SPRITETIME_H

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <d3dx9.h>
#include "Texture.h"

typedef struct Vertex2D_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}Vertex2D;


void Sprite_Initialize(void);
void Sprite_Finalize(void);
void Sprite_SetColor(D3DCOLOR color);
void Sprite_Draw(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float cx, float cy, float sx, float sy, float rotation);
void Sprite_DrawBG(void);




#endif
