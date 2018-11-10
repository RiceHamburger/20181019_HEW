#include "spritetime.h"
#include <math.h>
#include "texture.h"
#include"DirectX3D.h"

#define FVF_VERTEX2D ( D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_XYZRHW)

static D3DCOLOR g_Color = 0xffffffff;
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

void Sprite_Initialize(void)
{


	LPDIRECT3DDEVICE9 g_pD3DDevice = DirectX3DGetDevice();

	g_pD3DDevice->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	g_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);


}

void Sprite_Finalize(void)
{
	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

void Sprite_SetColor(D3DCOLOR color)
{
	g_Color = color;
}

void Sprite_Draw(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float cx, float cy, float sx, float sy, float rotation)
{
	float w = TextrueGetWidth(texture_index);
	float h = TextrueGetHeight(texture_index);
	float u0 = tx / w;
	float v0 = ty / h;
	float u1 = tx / w + tw / w;
	float v1 = ty / h + th / h;
	LPDIRECT3DDEVICE9 g_pD3DDevice = DirectX3DGetDevice();

	float px[4], py[4];
	px[0] = -cx * sx * cos(rotation) - -cy * sy * sin(rotation);
	py[0] = -cx * sx * sin(rotation) + -cy * sy * cos(rotation);
	px[1] = (-cx + tw) * sx * cos(rotation) - -cy * sy * sin(rotation);
	py[1] = (-cx + tw) * sx *sin(rotation) + -cy * sy * cos(rotation);
	px[2] = -cx * sx * cos(rotation) - (-cy + th) * sy * sin(rotation);
	py[2] = -cx * sx *sin(rotation) + (-cy + th) * sy * cos(rotation);
	px[3] = (-cx + tw) * sx * cos(rotation) - (-cy + th) * sy * sin(rotation);
	py[3] = (-cx + tw) * sx * sin(rotation) + (-cy + th) * sy * cos(rotation);


	//Sampler state setting
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 4);

	//LPDIRECT3DTEXTURE9 pTexture = DirectX3DGetTEXTURE(texture_index);

	g_pD3DDevice->SetTexture(0, DirectX3DGetTEXTURE(texture_index));
	//draw scene 
	Vertex2D f[] = {
		{ D3DXVECTOR4(px[0] + dx + cx - 0.5, py[0] + dy + cy - 0.5, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) },
		{ D3DXVECTOR4(px[1] + dx + cx - 0.5, py[1] + dy + cy - 0.5, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
		{ D3DXVECTOR4(px[2] + dx + cx - 0.5, py[2] + dy + cy - 0.5, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
		{ D3DXVECTOR4(px[3] + dx + cx - 0.5, py[3] + dy + cy - 0.5, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) }
	};

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, f, sizeof(Vertex2D));
}

void Sprite_DrawBG(void)
{

}


