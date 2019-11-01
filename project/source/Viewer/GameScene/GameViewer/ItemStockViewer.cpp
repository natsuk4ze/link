//=============================================================================
//
// ストックビュアー処理 [ItemStockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "ItemStockViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//数字のホップ量
static const float hopNumValue = 30.0f;

//数字の初期サイズ
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(42.0f, 42.0f, 0.0f);

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
ItemStockViewer::ItemStockViewer()
{
	//数字
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
	num->MakeVertex();
	num->size = initNumSize;
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.21f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	num->SetColor(SET_COLOR_NOT_COLORED);
	num->intervalNumberScr = 42.0f;
	num->intervalNumberTex = 0.10f;
	num->placeMax = 2;
	num->baseNumber = 10;
	num->isHopped = false;
	num->radian = 0;

	//アイコン
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Drill.png");
	icon->MakeVertex();
	icon->size = D3DXVECTOR3(180.0f, 135.0f, 0.0f);
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.7f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->SetColor(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ItemStockViewer::~ItemStockViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(icon);
}

//=============================================================================
// 更新処理
//=============================================================================
void ItemStockViewer::Update(void)
{
	//アニメーション
	Hop();
}

//=============================================================================
// 描画処理
//=============================================================================
void ItemStockViewer::Draw(void)
{
	//アイコン
	icon->Draw();
	icon->SetVertex();

	//数字
	num->DrawCounter(num->baseNumber, parameterBox, num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);
}

//=============================================================================
// アニメーション処理
//=============================================================================
void ItemStockViewer::Hop(void)
{
	//前フレームのパラメータとの差が0でないときホッピング状態にする
	currentParam = parameterBox;
	if (currentParam - lastParam != 0)
	{
		num->isHopped = true;
	}
	lastParam = parameterBox;

	//ホッピング処理
	num->size.y = num->HopNumber(num->size.y, initNumSize.y, hopNumValue);
}
