//=============================================================================
//
// ストックビュアー処理 [StockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "StockViewer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
StockViewer::StockViewer()
{
	for (int  i = 0; i < stockViewerMax; i++)
	{
		//数字
		num[i] = new CountViewerDrawer();
		num[i]->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
		num[i]->MakeVertex();
		num[i]->size = D3DXVECTOR3(7.50f, 15.0f, 0.0f);
		num[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		num[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.4f, SCREEN_HEIGHT / 10 * 2.70f + i*intervalViewerPos, 0.0f);
		num[i]->SetColor(SET_COLOR_NOT_COLORED);
		num[i]->parameterBox = 0;
		num[i]->intervalNumberScr = 120.0f;
		num[i]->intervalNumberTex = 0.10f;
		num[i]->placeMax = 1;
		num[i]->baseNumber = 10;

		//数字背景
		numBG[i] = new BaseViewerDrawer();
		numBG[i]->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/NumBG.png");
		numBG[i]->MakeVertex();
		numBG[i]->size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		numBG[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		numBG[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.4f, SCREEN_HEIGHT / 10 * 2.70f + i * intervalViewerPos, 0.0f);
		numBG[i]->SetColor(SET_COLOR_NOT_COLORED);

		//アイコン
		icon[i] = new BaseViewerDrawer();
		icon[i]->LoadTexture(iconTexPath[i]);
		icon[i]->MakeVertex();
		icon[i]->size = D3DXVECTOR3(65.0f, 65.0f, 0.0f);
		icon[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		icon[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1, SCREEN_HEIGHT / 10 * 2.70f + i * intervalViewerPos, 0.0f);
		icon[i]->SetColor(SET_COLOR_NOT_COLORED);

		//アイコン背景
		iconBG[i] = new BaseViewerDrawer();
		iconBG[i]->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/IconBG.png");
		iconBG[i]->MakeVertex();
		iconBG[i]->size = D3DXVECTOR3(65.0f, 65.0f, 0.0f);
		iconBG[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		iconBG[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1, SCREEN_HEIGHT / 10 * 2.70f + i * intervalViewerPos, 0.0f);
		iconBG[i]->SetColor(SET_COLOR_NOT_COLORED);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
StockViewer::~StockViewer()
{
	for (int i = 0; i < stockViewerMax; i++)
	{
		SAFE_DELETE(num[i]);
		SAFE_DELETE(numBG[i]);
		SAFE_DELETE(icon[i]);
		SAFE_DELETE(iconBG[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void StockViewer::Update(void)
{
	for (int i = 0; i < stockViewerMax; i++)
	{
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void StockViewer::Draw(void)
{
	for (int i = 0; i < stockViewerMax; i++)
	{
		//背景を先に描画
		iconBG[i]->Draw();
		iconBG[i]->SetVertex();

		icon[i]->Draw();
		icon[i]->SetVertex();

		//背景を先に描画
		numBG[i]->Draw();
		numBG[i]->SetVertex();

		num[i]->DrawCounter(num[i]->baseNumber, num[i]->parameterBox, num[i]->placeMax,
			num[i]->intervalNumberScr, num[i]->intervalNumberTex);
	}
}