//=============================================================================
//
// AIレベルビュアー処理 [LevelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "LevelViewer.h"

#include "../../../../main.h"
#include <string>
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
	//数字
	num = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.80f, SCREEN_HEIGHT / 10 * 1.30f),
		D3DXVECTOR2(initNumSize.x, initNumSize.y), "data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png", 65.0f, 0.1f, 4);

	//オーバーフロー用の数字
	overflowNum = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.90f, SCREEN_HEIGHT / 10 * 2.20f), 
		D3DXVECTOR2(initNumSize.x/2, initNumSize.y/2),"data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png", 35.0f, 0.1f, 6);

	//背景
	bg = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.20f),
		D3DXVECTOR2(250.0f, 250.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/BG.png");

	//テキスト
	text = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 0.60f),
		D3DXVECTOR2(180.0f, 49.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/Text.png");

	//＋
	plus = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.870f, SCREEN_HEIGHT / 10 * 2.20f),
		D3DXVECTOR2(60.0f, 60.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/Plus.png");

	//位の漢数字
	place = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.90f, SCREEN_HEIGHT / 10 * 1.50f), 
		D3DXVECTOR2(60.0f, 60.0f),"data/TEXTURE/Viewer/GameViewer/LevelViewer/PlaceText.png");
	place->SetTexture(2, 2, 3);
	place->SetColor(SET_COLOR_RIGHTBLUE);

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
	SAFE_DELETE(plus);
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
	//描画用ratioLevel設定
	SetDrawingRatioLevel();

	//数字ホッピング処理
	HopNumber();

	//ゲージ割合セット
	SetGaugePer();

	//桁のテクスチャを設定
	SetPlaceTex();
#ifdef _DEBUG
	Debug::Begin("LevelViewer");
	Debug::Text("AILevel:%f", parameterBox[LevelAI]);
	Debug::Text("currentFieldLevel:%f", parameterBox[CurrentFieldLevel]);
	Debug::End();
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void LevelViewer::Draw(void)
{
	//背景を先に描画
	bg->Draw();

	//ゲージ
	for (int i = 0; i < guageMax; i++)
	{
		circleGuage[i]->SetScale(D3DXVECTOR3(1.0f - (0.10f*(parameterBox[CurrentFieldLevel] - i)),
			1.0f - (0.10f*(parameterBox[CurrentFieldLevel] - i)), 0.0f));
		circleGuage[i]->Draw();
	}

	//テキスト
	text->Draw();

	if (IsOverflowed())
	{
		//＋
		plus->Draw();
		plus->position.x = (SCREEN_WIDTH / 10 * 9.870f) - overflowNum->intervalPosScr*(std::to_string((int)parameterBox[LevelAI] - 9999).length());
		//オーバーフロー数字
		overflowNum->DrawCounter(overflowNum->baseNumber, (int)parameterBox[LevelAI]-9999,
			overflowNum->intervalPosScr, overflowNum->intervalPosTex);

		//数字
		num->DrawCounter(num->baseNumber, 9999, num->placeMax,
			num->intervalPosScr, num->intervalPosTex);
	}
	else
	{
		//数字
		num->DrawCounter(num->baseNumber, (int)parameterBox[LevelAI], num->placeMax,
			num->intervalPosScr, num->intervalPosTex);
	}

	//place->Draw();
}

//=============================================================================
// 数字ホッピング処理
//=============================================================================
void LevelViewer::HopNumber(void)
{
	//前フレームのLevelAIより現在のLevelAIが大きい場合ホッピング状態にする
	if (isCurrentGreaterLast((float)parameterBox[LevelAI]))
	{
		//オーバーフロー中ならオーバーフロー数字を、そうでないなら通常の数字をホッピング
		IsOverflowed() ? overflowNum->isHopped = true : num->isHopped = true;
	}

	//数字のホップ量
	const float hopNumValue = 50.0f;
	num->size.y = num->HopNumber(num->size.y, initNumSize.y, hopNumValue);
	overflowNum->size.y = overflowNum->HopNumber(overflowNum->size.y, initNumSize.y/2, hopNumValue/2);
}

//=============================================================================
// ゲージ割合セット処理
//=============================================================================
void LevelViewer::SetGaugePer(void)
{
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
// 描画用ratioLevel設定処理
//=============================================================================
void LevelViewer::SetDrawingRatioLevel(void)
{
	//描画用RatioLevelの方がRatioLevelより小さい間、描画用RatioLevelを増加
	if (drawingRatioLevel < parameterBox[RatioLevel])
	{
		IncreaseDrawingRatioLevel();
	}

	//描画用RatioLevelの方がRatioLevelより大きい間、描画用RatioLevelを減少
	if (drawingRatioLevel > parameterBox[RatioLevel])
	{
		DecreaseDrawingRatioLevel();
	}
}

//=============================================================================
// 描画用ratiolevel増加処理
//=============================================================================
void LevelViewer::IncreaseDrawingRatioLevel(void)
{
	const float ratioIncreaseSpeed = 0.006f;

	drawingRatioLevel += ratioIncreaseSpeed;
	if (drawingRatioLevel >= parameterBox[RatioLevel])
	{
		drawingRatioLevel = parameterBox[RatioLevel];
	}
}

//=============================================================================
// 描画用ratiolevel減少処理
//=============================================================================
void LevelViewer::DecreaseDrawingRatioLevel(void)
{
	const float ratioDecreaseSpeed = 0.007f;

	drawingRatioLevel -= ratioDecreaseSpeed;
	if (drawingRatioLevel <= parameterBox[RatioLevel])
	{
		drawingRatioLevel = parameterBox[RatioLevel];
	}
}

//=============================================================================
// 漢数字の桁のテクスチャをセットする処理
//=============================================================================
void LevelViewer::SetPlaceTex(void)
{
	switch ((int)parameterBox[CurrentFieldLevel])
	{
	case FieldType::City:
		place->SetTexture(2,2,3);
		break;
	case FieldType::World:
		place->SetTexture(2, 2, 0);
		break;
	case FieldType::Space:
		place->SetTexture(2, 2, 1);
		break;
	default:
		break;
	}
}

//=============================================================================
//　オーバーフローしてるかどうかを返す処理
//=============================================================================
bool LevelViewer::IsOverflowed(void)
{
	//宇宙レベルでAIレベルが9999を超えたらオーバーフロー発生
	return (parameterBox[CurrentFieldLevel] == FieldType::Space) && (parameterBox[LevelAI]>9999);
}