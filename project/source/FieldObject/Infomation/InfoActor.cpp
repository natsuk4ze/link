//=====================================
//
// インフォアクター[InfoActor.cpp]
// 機能：フィールド上に情報を表示するための基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "InfoActor.h"
#include "../../../Framework/Camera/Camera.h"
#include "../../../Framework/Camera/ViewFrustum.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const float InfoActor::ActorSize = 10.0f;

//=====================================
// コンストラクタ
//=====================================
InfoActor::InfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(Vector3::One);
	this->SetActive(true);

	// 表示内容
	linkLevel = 12;
	int d[2];
	d[0] = linkLevel % 10;
	d[1] = linkLevel / 10;
	D3DXVECTOR3 dpos[2];
	dpos[0] = D3DXVECTOR3(128.0f, 128.0f, 0.0f);
	dpos[1] = D3DXVECTOR3(128.0f, 128.0f, 0.0f);
	for (int i = 0; i < 2; i++)
	{
		digit[i] = new DigitInfo(d[i], dpos[i]);
	}

	// ビューアの作成
	viewer = new Viewer3D(256, 256, D3DXVECTOR2(100.0f, 100.0f));
	viewer->SetPosition(D3DXVECTOR3(pos));
}

//=====================================
// デストラクタ
//=====================================
InfoActor::~InfoActor()
{
	SAFE_DELETE(viewer);

	for (int i = 0; i < 2; i++)
	{
		SAFE_DELETE(digit[i]);
	}
}

//=====================================
// 更新
//=====================================
void InfoActor::Update()
{
	if (!this->IsActive())
		return;

	for (int i = 0; i < 2; i++)
	{
		digit[i]->Update();
	}
}

//=====================================
// 描画
//=====================================
void InfoActor::Draw()
{
	if (!this->IsActive())
		return;

	viewer->Begin2D();
	for (int i = 0; i < 2; i++)
	{
		digit[i]->Draw();
	}
	viewer->End2D();

	//viewer->Draw3D();

}

//=====================================
// コンストラクタ
//=====================================
DigitInfo::DigitInfo(const int& num, const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	this->num = num;
	this->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
	this->SetSize(pos.x, pos.y);
	this->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=====================================
// デストラクタ
//=====================================
DigitInfo::~DigitInfo()
{
}

//=====================================
// 更新
//=====================================
void DigitInfo::Update()
{

}
