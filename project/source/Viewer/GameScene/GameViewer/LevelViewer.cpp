//=============================================================================
//
// AIレベルビュアー処理 [LevelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "LevelViewer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
LevelViewer::LevelViewer()
{
	//数字
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Num.png");
	num->MakeVertex();
	num->size = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.550f, SCREEN_HEIGHT / 10 * 1.50f, 0.0f);

	num->SetColor(SET_COLOR_NOT_COLORED);
	num->parameterBox = 0;
	num->intervalNumberScr = 40.0f;
	num->intervalNumberTex = 0.1f;
	num->placeMax = 5;
	num->baseNumber = 10;

	//背景
	circleGuage = new BaseViewerDrawer();
	circleGuage->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
	circleGuage->MakeVertex();
	circleGuage->size = D3DXVECTOR3(128.0f, 128.0f, 0.0f);
	circleGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	circleGuage->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.0f, SCREEN_HEIGHT / 10 * 1.50f, 0.0f);
	circleGuage->SetColor(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
LevelViewer::~LevelViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(circleGuage);
}

//=============================================================================
// 更新処理
//=============================================================================
void LevelViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void LevelViewer::Draw(void)
{
	//背景を先に描画
	circleGuage->Draw();
	circleGuage->SetVertex();

	num->DrawCounter(num->baseNumber, num->parameterBox, num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);
}