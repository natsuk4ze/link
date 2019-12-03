//=====================================
//
// ネームビュアー[NameViewer.cpp]
// 機能：名前表示用
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "NameViewer.h"

//=====================================
// コンストラクタ
//=====================================
NameViewer::NameViewer()
{
	for (int i = 0; i < NumChar; i++)
	{
		polygon[i] = new Polygon2D();
		polygon[i]->LoadTexture("data/TEXTURE/Alphabet/nameChar01.png");
	}
}

//=====================================
// デストラクタ
//=====================================
NameViewer::~NameViewer()
{
	for (int i = 0; i < NumChar; i++)
	{
		SAFE_DELETE(polygon[i]);
	}
}

//=====================================
// 更新
//=====================================
void NameViewer::Update()
{
	polygon[0]->SetPosition(stdPosition + D3DXVECTOR3(-interval, 0.0f, 0.0f));
	polygon[1]->SetPosition(stdPosition);
	polygon[2]->SetPosition(stdPosition + D3DXVECTOR3(interval, 0.0f, 0.0f));
}

//=====================================
// 描画
//=====================================
void NameViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (int i = 0; i < NumChar; i++)
	{
		polygon[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// 初期設定
//=====================================
void NameViewer::Init(const D3DXVECTOR3 & pos, const D3DXVECTOR2 & size)
{
	SetSize(size.x, size.y);
	SetPosition(pos);
}

//=====================================
// 名前のセット
//=====================================
void NameViewer::SetName(int * Buff)
{
	for (int i = 0; i < NumChar; i++, Buff++)
	{
		int x = *Buff % DivideX;
		int y = *Buff / DivideX;
		float left = (float)x * Width;
		float top = (float)y * Height;
		polygon[i]->SetUV(left, top, Width, Height);
	}
}

//=====================================
// 座標セット
//=====================================
void NameViewer::SetPosition(const D3DXVECTOR3 & pos)
{
	stdPosition = pos;
}

//=====================================
// サイズセット
//=====================================
void NameViewer::SetSize(const float & x, const float & y)
{
	for (int i = 0; i < NumChar; i++)
	{
		polygon[i]->SetSize(x, y);
	}
	interval = x * 2;
}
