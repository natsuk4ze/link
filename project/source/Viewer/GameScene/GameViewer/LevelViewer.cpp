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

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

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
	num = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.80f, SCREEN_HEIGHT / 10 * 1.30f),D3DXVECTOR2(initNumSize.x, initNumSize.y), 
		"data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png", 65.0f, 0.1f, 4);

	//オーバーフロー用の数字
	overflowNum = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.90f, SCREEN_HEIGHT / 10 * 2.20f), D3DXVECTOR2(initNumSize.x/2, initNumSize.y/2),
		"data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png", 35.0f, 0.1f, 6);

	//背景
	bg = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.20f),
		D3DXVECTOR2(250.0f, 250.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/BG.png");

	//テキスト
	text = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 0.60f),
		D3DXVECTOR2(180.0f, 49.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/Text.png");

	//位の漢数字
	place = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.90f, SCREEN_HEIGHT / 10 * 1.20f),
		D3DXVECTOR2(100.0f, 100.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/PlaceText.png");
	place->SetTexture(2, 2, 0);

	//円ゲージ
	for (int i = 0; i < guageMax; i++)
	{
		circleGuage[i] = new CircleGauge(D3DXVECTOR2(250.0f, 250.0f));
		circleGuage[i]->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
		circleGuage[i]->SetScale(D3DXVECTOR3(1.0f, 1.0f, 0.0f));
		circleGuage[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f));
		circleGuage[i]->SetFillStart(circleGuage[i]->Top);
		circleGuage[i]->SetPercent(0.0f);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
LevelViewer::~LevelViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(overflowNum);
	SAFE_DELETE(bg);
	SAFE_DELETE(text);
	SAFE_DELETE(place);
	for (int i = 0; i < guageMax; i++)
	{
		SAFE_DELETE(circleGuage[i]);
	}
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

#ifdef _DEBUG
	Debug::Begin("LevelViewer");
	Debug::Text("AILevel:%f", parameterBox[LevelAI]);
	Debug::Text("currentFieldLevel:%f", parameterBox[CurrentFieldLevel]);
	Debug::End();
#endif

	//ゲージ初期化
	if ((int)parameterBox[CurrentFieldLevel] == 0)
	{
		for (int i = 0; i < guageMax; i++)
		{
			if (i == 0)continue;
			circleGuage[i]->SetPercent(0.0f);
		}
	}
	circleGuage[(int)parameterBox[CurrentFieldLevel]]->SetPercent(drawingRatioLevel);
}

//=============================================================================
// 描画処理
//=============================================================================
void LevelViewer::Draw(void)
{
	if (!isPlaying) return;

	//背景を先に描画
	bg->Draw();

	for (int i = 0; i < guageMax; i++)
	{
		circleGuage[i]->SetScale(D3DXVECTOR3(1.0f - (0.10f*(parameterBox[CurrentFieldLevel] - i)),
			1.0f - (0.10f*(parameterBox[CurrentFieldLevel] - i)), 0.0f));
		circleGuage[i]->Draw();
	}

	num->DrawCounter(num->baseNumber, (int)parameterBox[LevelAI], num->placeMax,
		num->intervalPosScr, num->intervalPosTex);

	text->Draw();

	//オーバーフロー中なら描画（調整中）
	if (IsOverflowed())
	{
		overflowNum->DrawCounter(overflowNum->baseNumber, (int)parameterBox[LevelAI]-9999,
			overflowNum->intervalPosScr, overflowNum->intervalPosTex);
	}
	//place->Draw();
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

//=============================================================================
//　オーバーフローしてるかどうかを返す処理
//=============================================================================
bool LevelViewer::IsOverflowed(void)
{
	//宇宙レベルでAIレベルが9999を超えたらオーバーフロー発生
	return (parameterBox[CurrentFieldLevel] == 2) && (parameterBox[LevelAI]>9999);
}
