//=============================================================================
//
// タイマービュアー処理 [TimerViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "TimerViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
TimerViewer::TimerViewer()
{
	isPlaying = true;

	//整数部
	intNum = new CountViewerDrawer();
	intNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	intNum->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	intNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	intNum->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.3f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	intNum->intervalPosScr = 80.0f;
	intNum->intervalPosTex = 0.1f;
	intNum->placeMax = 3;
	intNum->baseNumber = 10;
	intNum->MakeVertex();

	//小数部
	fewNum = new CountViewerDrawer();
	fewNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	fewNum->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	fewNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fewNum->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.70f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	fewNum->intervalPosScr = 80.0f;
	fewNum->intervalPosTex = 0.1f;
	fewNum->placeMax = 2;
	fewNum->baseNumber = 10;
	fewNum->MakeVertex();

	//小数点
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Point.png");
	point->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(intNum->position.x + intNum->intervalPosScr*2.80f, SCREEN_HEIGHT / 10 * 1.0f,0.0f);
	point->MakeVertex();

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/BG.png");
	bg->size = D3DXVECTOR3(460.0f, 200.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 1.250), SCREEN_HEIGHT / 10 * 0.920f, 0.0f);
	bg->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
TimerViewer::~TimerViewer()
{
	SAFE_DELETE(intNum);
	SAFE_DELETE(fewNum);
	SAFE_DELETE(point);
	SAFE_DELETE(bg);
}

//=============================================================================
// 更新処理
//=============================================================================
void TimerViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void TimerViewer::Draw(void)
{
	if (!isPlaying)
		return;

	//背景を先に描画
	bg->Draw();

	//小数点
	point->Draw();

	//整数部
	intNum->DrawCounter(intNum->baseNumber,
		(int)parameterBox, intNum->placeMax,
		intNum->intervalPosScr, intNum->intervalPosTex);

	//小数部
	fewNum->DrawCounter(fewNum->baseNumber, 
		(int)((parameterBox - (int)parameterBox)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
		fewNum->intervalPosScr, fewNum->intervalPosTex);
}