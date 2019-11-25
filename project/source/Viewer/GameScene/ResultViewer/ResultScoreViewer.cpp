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
ResultScoreViewer::ResultScoreViewer()
{
	for (int i = 0; i < fieldTypeMax; i++)
	{
		num[i] = new CountViewerDrawer();
		num[i]->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/Number.png");
		num[i]->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
		num[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		num[i]->intervalPosScr = 80.0f;
		num[i]->intervalPosTex = 0.1f;
		num[0]->placeMax = 5;
		num[1]->placeMax = 5;
		num[2]->placeMax = 6;
		num[i]->baseNumber = 16;
		num[i]->position = D3DXVECTOR3(SCREEN_WIDTH/5*3 - i*num[i]->placeMax*num[i]->intervalPosScr, SCREEN_CENTER_Y, 0.0f);
		num[i]->MakeVertex();
	}
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
			parameterBox[0], num[i]->placeMax,
			num[i]->intervalPosScr, num[i]->intervalPosTex);
	}
}