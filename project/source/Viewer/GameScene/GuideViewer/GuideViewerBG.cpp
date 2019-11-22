//=====================================
//
// ガイドビュアーバックグラウンド[GuideViewerBG.cpp]
// 機能：ガイドビュアーの背景
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideViewerBG.h"
#include "../../../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
GuideViewerBG::GuideViewerBG()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("GuideViewerBG", polygon);

	transform->Rotate(0.0f, 0.0f, 0.0f);
	transform->SetPosition(D3DXVECTOR3(0.0f, 50.0f, 50.0f));
	transform->SetScale(Vector3::One);
}

//=====================================
// デストラクタ
//=====================================
GuideViewerBG::~GuideViewerBG()
{
	SAFE_DELETE(polygon);
}

//=====================================
// 更新
//=====================================
void GuideViewerBG::Update()
{

}

//=====================================
// 描画
//=====================================
void GuideViewerBG::Draw()
{
	polygon->Draw(transform->GetMatrix());
}
