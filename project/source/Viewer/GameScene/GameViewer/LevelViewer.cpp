//=============================================================================
//
// AIレベルビュアー処理 [LevelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "GameViewer.h"
#include "GameViewerParam.h"
#include "../../../../Framework/Renderer2D/CircleGauge.h"
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
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png");
	num->MakeVertex();
	num->size = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.550f, SCREEN_HEIGHT / 10 * 1.50f, 0.0f);

	num->SetColor(SET_COLOR_RIGHTBLUE);
	num->parameterBox = 0;
	num->intervalNumberScr = 40.0f;
	num->intervalNumberTex = 0.1f;
	num->placeMax = 5;
	num->baseNumber = 10;

	//円ゲージ
	circleGuage = new CircleGauge(D3DXVECTOR2(128.0f, 128.0f));
	circleGuage->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
	circleGuage->SetScale(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	circleGuage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	circleGuage->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.0f, SCREEN_HEIGHT / 10 * 1.50f, 0.0f));
	circleGuage->SetFillStart(circleGuage->Top);
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
	circleGuage->SetPercent(0.75f);
	circleGuage->Draw();

	num->DrawCounter(num->baseNumber, num->parameterBox, num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);
}

//=============================================================================
// パラメータ更新処理
//=============================================================================
void LevelViewer::UpdateParam(void)
{
	GameViewerParam param;

	gameViewer->ReceiveParam(param);
	num->parameterBox = param.levelAI;
}