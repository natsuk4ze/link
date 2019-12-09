//=============================================================================
//
// AIレベルビュアー処理 [LevelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "LevelViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/CircleGauge.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//数字の初期サイズ
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(140.0f, 140.0f, 0.0f);

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
LevelViewer::LevelViewer()
{
	isPlaying = true;

	//数字
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png");
	num->size = initNumSize;
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.80f, SCREEN_HEIGHT / 10 * 1.30f, 0.0f);
	num->intervalPosScr = 65.0f;
	num->intervalPosTex = 0.1f;
	num->placeMax = 4;
	num->baseNumber = 10;
	num->MakeVertex();

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/BG.png");
	bg->size = D3DXVECTOR3(250.0f, 250.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f);
	bg->MakeVertex();

	//円ゲージ
	circleGuage = new CircleGauge(D3DXVECTOR2(250.0f, 250.0f));
	circleGuage->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
	circleGuage->SetScale(D3DXVECTOR3(1.0f, 1.0f, 0.0f));
	circleGuage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	circleGuage->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f));
	circleGuage->SetFillStart(circleGuage->Top);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
LevelViewer::~LevelViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(bg);
	SAFE_DELETE(circleGuage);
}

//=============================================================================
// 更新処理
//=============================================================================
void LevelViewer::Update(void)
{
	//現在のフレームのパラメータとしてセット
	currentParam[LevelAI] = (int)parameterBox[LevelAI];

	//描画用ratioLevel設定
	SetDrawingRatioLevel();

	//数字ホッピング処理
	HopNumber();

	//前フレームのパラメータとしてセット
	lastParam[LevelAI] = (int)parameterBox[LevelAI];
}

//=============================================================================
// 描画処理
//=============================================================================
void LevelViewer::Draw(void)
{
	if (!isPlaying)
		return;

	//背景を先に描画
	bg->Draw();

	//円ゲージ
	circleGuage->SetPercent(drawingRatioLevel);
	circleGuage->Draw();

	//数宇
	num->DrawCounter(num->baseNumber, (int)parameterBox[LevelAI], num->placeMax,
		num->intervalPosScr, num->intervalPosTex);
}

//=============================================================================
// 数字ホッピング処理
//=============================================================================
void LevelViewer::HopNumber(void)
{
	//数字のホップ量
	const float hopNumValue = 50.0f;

	//前フレームのLevelAIより現在のLevelAIが大きい場合ホッピング状態にする
	if (currentParam[LevelAI] - lastParam[LevelAI] > 0)
	{
		num->isHopped = true;
	}

	//ホッピング処理
	num->size.y = num->HopNumber(num->size.y, initNumSize.y, hopNumValue);
}

//=============================================================================
// 描画用ratioLevel設定処理
//=============================================================================
void LevelViewer::SetDrawingRatioLevel(void)
{
	//前フレームのLevelAIより現在のLevelAIが大きい場合
	if (currentParam[LevelAI] - lastParam[LevelAI] > 0)
	{
		if (isLevelAI_Decreasing)
		{
			isLevelAI_Decreasing = false;
		}
		isLevelAI_Increasing = true;
	}

	//描画用RatioLevel増加
	IncreaseDrawingRatioLevel();

	//前フレームのLevelより現在のLevelAIが小さい場合
	if (currentParam[LevelAI] - lastParam[LevelAI] < 0)
	{
		if (isLevelAI_Increasing)
		{
			isLevelAI_Increasing = false;
		}

		isLevelAI_Decreasing = true;
	}

	//描画用RatioLevel減少
	DecreaseDrawingRatioLevel();
}

//=============================================================================
// 描画用ratiolevel増加処理
//=============================================================================
void LevelViewer::IncreaseDrawingRatioLevel(void)
{
	//LevelAIが増加中なら実行
	if (!isLevelAI_Increasing) return;

	//ratioLevelの増加スピード
	const float ratioIncreaseSpeed = 0.005f;

	//描画用RatioLevelの方がRatioLevelより小さい間、描画用RatioLevelを増加
	if (drawingRatioLevel < parameterBox[RatioLevel])
	{
		drawingRatioLevel += ratioIncreaseSpeed;
		if (drawingRatioLevel >= parameterBox[RatioLevel])
		{
			drawingRatioLevel = parameterBox[RatioLevel];
			isLevelAI_Increasing = false;
		}
	}

	//一周したか
	if (drawingRatioLevel > parameterBox[RatioLevel])
	{
		if (drawingRatioLevel < 1.0f)
		{
			drawingRatioLevel += ratioIncreaseSpeed;
		}
		else
		{
			drawingRatioLevel = 0.0f;
		}
	}
}

//=============================================================================
// 描画用ratiolevel減少処理
//=============================================================================
void LevelViewer::DecreaseDrawingRatioLevel(void)
{
	//LevelAIが減少中なら実行
	if (!isLevelAI_Decreasing) return;

	//ratioLevelの減少スピード
	const float ratioDecreaseSpeed = 0.05f;

	//描画用RatioLevelの方がRatioLevelより大きい間、描画用RatioLevelを減少
	if (drawingRatioLevel > parameterBox[RatioLevel])
	{
		drawingRatioLevel -= ratioDecreaseSpeed;
		if (drawingRatioLevel <= parameterBox[RatioLevel])
		{
			drawingRatioLevel = parameterBox[RatioLevel];
			isLevelAI_Decreasing = false;
		}
	}

	//一周したか
	if (drawingRatioLevel < parameterBox[RatioLevel])
	{
		if (drawingRatioLevel > 0.0f)
		{
			drawingRatioLevel -= ratioDecreaseSpeed;
		}
		else
		{
			drawingRatioLevel = 1.0f;
		}
	}
}
