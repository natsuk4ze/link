//=============================================================================
//
// 結果スコアビュアー処理 [ResultScoreViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "ResultScoreViewer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
ResultScoreViewer::ResultScoreViewer() :parameterBox()
{
	//*****************
	// テクスチャの読み込みリファクタリング中
	//*****************
	for (int i = 0; i < fieldTypeMax; i++)
	{
		num[i] = new CountViewerDrawer();
		num[i]->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/Number.png");
		num[i]->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
		num[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		num[i]->intervalPosScr = 80.0f;
		num[i]->intervalPosTex = 0.1f;
		num[i]->baseNumber = 10;
	}

	SetViewerPos();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ResultScoreViewer::~ResultScoreViewer()
{
	for (int i = 0; i < fieldTypeMax; i++)
	{
		SAFE_DELETE(num[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void ResultScoreViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void ResultScoreViewer::Draw(void)
{
	for (int i = 0; i < fieldTypeMax; i++)
	{
		num[i]->DrawCounter(num[i]->baseNumber,
			parameterBox[i], num[i]->placeMax,
			num[i]->intervalPosScr, num[i]->intervalPosTex);
	}
}

//=============================================================================
// ビュアー座標設定処理（リファクタリング予定）
//=============================================================================
void ResultScoreViewer::SetViewerPos(void)
{
	num[0]->placeMax = 4;
	num[1]->placeMax = 4;
	num[2]->placeMax = 8;

	for (int i = 0; i < fieldTypeMax; i++)
	{
		int placeCnt[fieldTypeMax] = {
			num[0]->placeMax,
			num[0]->placeMax + num[1]->placeMax,
			num[0]->placeMax + num[1]->placeMax + num[2]->placeMax };

		float pos = placeCnt[i] * num[i]->intervalPosScr;

		num[i]->position = D3DXVECTOR3(
			SCREEN_WIDTH/2 
			+ num[i]->intervalPosScr/2 
			+ (num[0]->placeMax + num[1]->placeMax + num[2]->placeMax)/2*num[i]->intervalPosScr 
			- pos, SCREEN_CENTER_Y/2, 0.0f);
		num[i]->MakeVertex();
	}
}