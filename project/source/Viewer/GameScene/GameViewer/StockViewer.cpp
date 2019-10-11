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
const int StockViewer::stockViewerMax;

//ビュアーの表示間隔
static const float intervalViewerPos = 185.0f;

//アイテムアイコンテクスチャパス
static const char *iconTexPath[StockViewer::stockViewerMax]
{
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Bridge/BridgeIcon.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Drill/DrillIcon.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Insurance/InsuranceIcon.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/EDF/EDF_Icon.png",
};

//数字のホップ量
static const float hopNumValue = 30.0f;

//数字の初期サイズ
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(7.50f, 15.0f, 0.0f);

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
		num[i]->size = initNumSize;
		num[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		num[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.4f, SCREEN_HEIGHT / 10 * 2.70f + i*intervalViewerPos, 0.0f);
		num[i]->SetColor(SET_COLOR_NOT_COLORED);
		parameterBox[i] = 0;
		num[i]->intervalNumberScr = 120.0f;
		num[i]->intervalNumberTex = 0.10f;
		num[i]->placeMax = 1;
		num[i]->baseNumber = 10;
		num[i]->isHopped = false;
		num[i]->radian = 0;

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
	Animate();
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

		num[i]->DrawCounter(num[i]->baseNumber, parameterBox[i], num[i]->placeMax,
			num[i]->intervalNumberScr, num[i]->intervalNumberTex);
	}
}

//=============================================================================
// アニメーション処理
//=============================================================================
void StockViewer::Animate(void)
{
	for (int i = 0; i < stockViewerMax; i++)
	{
		//ホッピング処理
		num[i]->size.y = num[i]->HopNumber(num[i]->size.y, initNumSize.y, hopNumValue);
	}
}
