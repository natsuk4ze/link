//=====================================
//
// リンクインフォアクター[LinkInfoActor.h]
// 機能：リンクレベル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// スタティックメンバ初期化
//**************************************
const D3DXVECTOR3 LinkInfoActor::digitPos[] =
{ D3DXVECTOR3(160.0f, 160.0f, 0.0f),
D3DXVECTOR3(96.0f, 160.0f, 0.0f) };
const D3DXVECTOR3 LinkInfoActor::logoPos = D3DXVECTOR3(128.8f, 80.0f, 0.0f);
const D3DXVECTOR2 LinkInfoActor::logoSize = D3DXVECTOR2(100.0f, 100.0f);
const D3DXVECTOR3 LinkInfoActor::upPos[] = { 
	D3DXVECTOR3(-3.0f ,20.0f, 3.0f),
	D3DXVECTOR3(-3.0f ,20.0f, 3.0f),
	D3DXVECTOR3(-3.0f ,10.0f, 3.0f)
};

//=====================================
// コンストラクタ
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& townPos, const int& townLevel, Field::FieldLevel current):
	InfoActor(townPos + upPos[current]), linkLevel(townLevel)
{
	// ロゴ表示
	logo = new Polygon2D();
	logo->SetPosition(logoPos);
	logo->LoadTexture("data/TEXTURE/Logo/Logo.png");
	logo->SetSize(logoSize.x, logoSize.y);
	logo->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	logo->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// レベル表示
	linkLevel = Math::Clamp(0, 99, linkLevel);
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i] = new InfoDigit(digit[i], digitPos[i]);
	}

}

//=====================================
// デストラクタ
//=====================================
LinkInfoActor::~LinkInfoActor()
{
	for (int i = 0; i < MaxDigit; i++)
	{
		SAFE_DELETE(digitActor[i]);
	}

	SAFE_DELETE(logo);
}

//=====================================
// 更新
//=====================================
void LinkInfoActor::Update()
{
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i]->Update();
	}
}

//=====================================
// 描画
//=====================================
void LinkInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	// あとでコントローラに移動
	LPDIRECT3DDEVICE9 device = GetDevice();
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	viewer->Begin2D();
	logo->Draw();
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i]->Draw();
	}
	viewer->End2D();

	viewer->Draw3D();

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

}

//=====================================
// レベル変更時使用
//=====================================
void LinkInfoActor::SetLevel(const int& nextLevel)
{
	linkLevel = nextLevel;
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i]->ChangeDigit(digit[i]);
	}
}
