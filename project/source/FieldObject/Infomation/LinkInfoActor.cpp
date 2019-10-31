//=====================================
//
// リンクインフォアクター[LinkInfoActor.h]
// 機能：リンクレベル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& pos, const int& level):
	InfoActor(pos), linkLevel(level)
{
	// ロゴ表示
	logo = new Polygon2D();
	logo->SetPosition(D3DXVECTOR3(128.0f, 80.0f, 0.0f));
	logo->LoadTexture("data/TEXTURE/Logo/Logo.png");
	logo->SetSize(100.0f, 100.0f);
	logo->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	logo->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// レベル表示
	int d[2];
	d[0] = linkLevel % 10;
	d[1] = linkLevel / 10;
	D3DXVECTOR3 dpos[2];
	dpos[0] = D3DXVECTOR3(160.0f, 160.0f, 0.0f);
	dpos[1] = D3DXVECTOR3(96.0f, 160.0f, 0.0f);
	for (int i = 0; i < 2; i++)
	{
		digitActor[i] = new InfoDigit(d[i], dpos[i]);
	}

}

//=====================================
// デストラクタ
//=====================================
LinkInfoActor::~LinkInfoActor()
{
	for (int i = 0; i < 2; i++)
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
	for (int i = 0; i < 2; i++)
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
	for (int i = 0; i < 2; i++)
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
	//digit[0] = linkLevel % 10;
	//digit[1] = linkLevel / 10;
}
