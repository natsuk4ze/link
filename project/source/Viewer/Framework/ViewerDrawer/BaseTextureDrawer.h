//=============================================================================
//
// テクスチャ描画クラス [BaseTextureDrawer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BaseTextureDrawer_H_
#define _BaseTextureDrawer_H_

#include "../../../../Framework/Math/Easing.h"
#include <functional>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 色定義
#define SET_COLOR_NOT_COLORED	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define SET_COLOR_BLACK			(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define SET_COLOR_RED			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define SET_COLOR_GREEN			(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define SET_COLOR_BLUE			(D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))
#define SET_COLOR_YELLOW		(D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define SET_COLOR_PINK			(D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))
#define SET_COLOR_RIGHTBLUE		(D3DXCOLOR(0.0f,1.0f,1.0f,1.0f))
#define SET_COLOR_ORANGE		(D3DXCOLOR(1.0f,0.4f,0.0f,1.0f))

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BaseTextureDrawer
{
protected:
	VERTEX_2D Vertex[NUM_VERTEX];
	LPDIRECT3DTEXTURE9 Texture = nullptr;

	D3DXVECTOR3	Position;
	D3DXVECTOR2	Size;
	bool Visible = true;

public:
	BaseTextureDrawer();
	virtual ~BaseTextureDrawer();

	void Draw();
	void LoadTexture(const char *path);
	void LoadTexture(LPDIRECT3DTEXTURE9* Texture);
	void SetSize(const D3DXVECTOR2 Size);
	void SetAlpha(float alpha);
	void SetColor(D3DXCOLOR color);
	void SetVisible(bool Flag) { this->Visible = Flag; };
	D3DXVECTOR3 GetPosition(void) { return this->Position; };
};

#endif