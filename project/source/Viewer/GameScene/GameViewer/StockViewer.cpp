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
// グローバル変数
//*****************************************************************************

//ストックビュアーの種類数
const int StockViewer::typeMax;

//ビュアーの表示間隔
static const float intervalViewerPos = 220.0f;

//アイテムアイコンテクスチャパス
static const char *iconTexPath[StockViewer::typeMax]
{
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Bridge.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Drill.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Insurance.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/EDF.png",
};

//数字のホップ量
static const float hopNumValue = 30.0f;

//数字の初期サイズ
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(20.0f, 46.0f, 0.0f);

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
StockViewer::StockViewer()
{
	for (int  i = 0; i < typeMax; i++)
	{
		//数字
		num[i] = new CountViewerDrawer();
		num[i]->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
		num[i]->MakeVertex();
		num[i]->size = initNumSize;
		num[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		num[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.3f, SCREEN_HEIGHT / 10 * 2.50f + i*intervalViewerPos, 0.0f);
		num[i]->SetColor(SET_COLOR_NOT_COLORED);
		parameterBox[i] = 0;
		num[i]->intervalNumberScr = 120.0f;
		num[i]->intervalNumberTex = 0.10f;
		num[i]->placeMax = 1;
		num[i]->baseNumber = 10;
		num[i]->isHopped = false;
		num[i]->radian = 0;

		//アイコン
		icon[i] = new BaseViewerDrawer();
		icon[i]->LoadTexture(iconTexPath[i]);
		icon[i]->MakeVertex();
		icon[i]->size = D3DXVECTOR3(180.0f, 135.0f, 0.0f);
		icon[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		icon[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.7f, SCREEN_HEIGHT / 10 * 2.50f + i * intervalViewerPos, 0.0f);
		icon[i]->SetColor(SET_COLOR_NOT_COLORED);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
StockViewer::~StockViewer()
{
	for (int i = 0; i < typeMax; i++)
	{
		SAFE_DELETE(num[i]);
		SAFE_DELETE(icon[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void StockViewer::Update(void)
{
	Animate();
}

//=============================================================================
// 描画処理
//=============================================================================
void StockViewer::Draw(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		icon[i]->Draw();
		icon[i]->SetVertex();

		num[i]->DrawCounter(num[i]->baseNumber, parameterBox[i], num[i]->placeMax,
			num[i]->intervalNumberScr, num[i]->intervalNumberTex);
	}
}

//=============================================================================
// アニメーション処理
//=============================================================================
void StockViewer::Animate(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		//ホッピング処理
		num[i]->size.y = num[i]->HopNumber(num[i]->size.y, initNumSize.y, hopNumValue);
	}
}
