//=====================================
//
// ガイドビュアーエフェクト[GuideViewerEffect.h]
// 機能：ガイドビュアーのエフェクト
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideViewerEffect.h"
#include "GuideViewer.h"

//=====================================
// コンストラクタ
//=====================================
GuideViewerEffect::GuideViewerEffect()
{
	polygon = new Polygon2D();
	polygon->LoadTexture("data/TEXTURE/Viewer/GameViewer/GuideViewer/White-Effect.png");
	polygon->SetSize(GuideViewer::SubScreenSize.x, GuideViewer::SubScreenSize.y);
	polygon->SetActive(true);
	polygon->SetPosition(Vector3::Zero);
	polygon->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	polygon->SetColor(D3DXCOLOR(0.615f, 0.800f, 1.0f, 0.800f));
}

//=====================================
// デストラクタ
//=====================================
GuideViewerEffect::~GuideViewerEffect()
{
	SAFE_DELETE(polygon);
}

//=====================================
// 更新
//=====================================
void GuideViewerEffect::Update()
{
}

//=====================================
// 描画
//=====================================
void GuideViewerEffect::Draw()
{
	polygon->Draw();
}
