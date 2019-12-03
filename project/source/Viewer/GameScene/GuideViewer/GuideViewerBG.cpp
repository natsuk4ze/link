//=====================================
//
// ガイドビュアーバックグラウンド[GuideViewerBG.cpp]
// 機能：ガイドビュアーの背景
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideViewerBG.h"
#include "../../../../Framework/Resource/ResourceManager.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../Framework/ViewerDrawer/PolygonDrawer.h"


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
const int WallNum = 2;

//=============================================================================
// コンストラクタ
//=============================================================================
GuideViewerBG::GuideViewerBG()
{
	ResourceManager::Instance()->MakePolygon("GuideViewerBG", "data/TEXTURE/Viewer/GameViewer/GuideViewer/Background.png",
		D3DXVECTOR2(5.7735f * 10.0f, 5.7735f * 10.0f));
	ResourceManager::Instance()->MakePolygon("Wall", "data/TEXTURE/Viewer/GameViewer/GuideViewer/Wall.png", { 8.0f, 4.5f });

	background = new PolygonDrawer("GuideViewerBG", D3DXVECTOR3(0.0f, 10.0f, 100.0f));

	for (int i = 0; i < WallNum; i++)
	{
		LeftWall.push_back(new PolygonDrawer("Wall", D3DXVECTOR3(0.0f, 10.0f, 150.0f), D3DXVECTOR3(-5.7735f * 2, 10.0f, -5.0f), i));
		RightWall.push_back(new PolygonDrawer("Wall", D3DXVECTOR3(0.0f, 10.0f, 150.0f), D3DXVECTOR3(5.7735f * 2, 10.0f, -5.0f), i));
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
GuideViewerBG::~GuideViewerBG()
{
	SAFE_DELETE(background);
	Utility::DeleteContainer(LeftWall);
	Utility::DeleteContainer(RightWall);
}

//=============================================================================
// 更新
//=============================================================================
void GuideViewerBG::Update(void)
{
	for (auto &Polygon : LeftWall)
	{
		Polygon->Update();
	}

	for (auto &Polygon : RightWall)
	{
		Polygon->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void GuideViewerBG::Draw(void)
{
	background->Draw();

	for (auto &Polygon : LeftWall)
	{
		Polygon->Draw();
	}

	for (auto &Polygon : RightWall)
	{
		Polygon->Draw();
	}
}