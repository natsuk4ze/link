//=====================================
//
// タイトルロゴ[TitleLogo.cpp]
// 機能：タイトルロゴ表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "TitleLogo.h"

//**************************************
// クラス定義
//**************************************
const D3DXVECTOR3 TitleLogo::InitPos = D3DXVECTOR3(960.0f, 300.0f, 0.0f);
const D3DXVECTOR2 TitleLogo::InitSize = D3DXVECTOR2(512.0f, 512.0f);

//=====================================
// コンストラクタ
//=====================================
TitleLogo::TitleLogo()
{
	this->LoadTexture("data/TEXTURE/Logo/Logo.png");
	this->SetSize(InitSize.x, InitSize.y);
	this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	this->SetUV(0.0f, 0.0f, 1.0f, 1.0f);

	transform->SetPosition(InitPos);
}

//=====================================
// デストラクタ
//=====================================
TitleLogo::~TitleLogo()
{
}

//=====================================
// 更新
//=====================================
void TitleLogo::Update()
{
}

//=====================================
// 描画
//=====================================
void TitleLogo::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	Polygon2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
