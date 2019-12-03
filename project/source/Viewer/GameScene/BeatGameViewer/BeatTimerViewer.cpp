//=============================================================================
//
// タイマービュアー処理 [BeatTimerViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "BeatTimerViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
BeatTimerViewer::BeatTimerViewer()
{
	//整数部
	intNum = new CountViewerDrawer();
	intNum->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Number.png");
	intNum->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	intNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	intNum->position = D3DXVECTOR3(SCREEN_WIDTH/10*4.80f, SCREEN_HEIGHT/4, 0.0f);
	intNum->intervalPosScr = 80.0f;
	intNum->intervalPosTex = 0.1f;
	intNum->placeMax = 1;
	intNum->baseNumber = 10;
	intNum->MakeVertex();

	//小数点
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Point.png");
	point->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(intNum->position.x + intNum->intervalPosScr/2, SCREEN_HEIGHT/4, 0.0f);
	point->MakeVertex();

	//小数部
	fewNum = new CountViewerDrawer();
	fewNum->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Number.png");
	fewNum->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	fewNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fewNum->position = D3DXVECTOR3(point->position.x + intNum->intervalPosScr/2, SCREEN_HEIGHT/4, 0.0f);
	fewNum->intervalPosScr = 70.0f;
	fewNum->intervalPosTex = 0.1f;
	fewNum->placeMax = 2;
	fewNum->baseNumber = 10;
	fewNum->MakeVertex();
	
	//前のテキスト
	frontText = new BaseViewerDrawer();
	frontText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Text.png");
	frontText->size = D3DXVECTOR3(200.0f, 150.0f, 0.0f);
	frontText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frontText->position = D3DXVECTOR3(intNum->position.x - intNum->intervalPosScr*1.50f, SCREEN_HEIGHT/4 - 5.0f, 0.0f);
	frontText->MakeVertex();
	frontText->SetTexture(1, 2, 0);

	//後ろのテキスト
	backText = new BaseViewerDrawer();
	backText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Text.png");
	backText->size = D3DXVECTOR3(200.0f, 150.0f, 0.0f);
	backText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	backText->position = D3DXVECTOR3(fewNum->position.x + intNum->intervalPosScr*fewNum->placeMax, SCREEN_HEIGHT/4 - 5.0f, 0.0f);
	backText->MakeVertex();
	backText->SetTexture(1, 2, 1);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BeatTimerViewer::~BeatTimerViewer()
{
	SAFE_DELETE(intNum);
	SAFE_DELETE(fewNum);
	SAFE_DELETE(point);
	SAFE_DELETE(frontText);
	SAFE_DELETE(backText);
}

//=============================================================================
// 更新処理
//=============================================================================
void BeatTimerViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void BeatTimerViewer::Draw(void)
{
	//背景を先に描画
	frontText->Draw();

	//背景を先に描画
	backText->Draw();

	//小数点
	point->Draw();

	//整数部
	intNum->DrawCounter(intNum->baseNumber,
		(int)time, intNum->placeMax,
		intNum->intervalPosScr, intNum->intervalPosTex);

	//小数部
	fewNum->DrawCounter(fewNum->baseNumber,
		(int)((time - (int)time)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
		fewNum->intervalPosScr, fewNum->intervalPosTex);
}

//=============================================================================
// セット処理
//=============================================================================
void BeatTimerViewer::Set(float time)
{
	//タイマーをセット
	this->time = time;
}
