//=============================================================================
//
// AIレベルビュアー処理 [LevelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/CircleGauge.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "../../Framework/ViewerDrawer/RotateViewerDrawer.h"
#include "LevelViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// *注意:(11/01現在)矢印関連処理はいらなくなるかもしれないので決まるまでは
// 一旦、雑に実装
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//矢印のテクスチャパス
static const char *arrowTexPath[LevelViewer::typeMax]
{
	"data/TEXTURE/Viewer/GameViewer/LevelViewer/LevelUpArrow.png",
	"data/TEXTURE/Viewer/GameViewer/LevelViewer/LevelDownArrow.png",
};

//数字の初期サイズ
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(70.0f, 70.0f, 0.0f);

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
LevelViewer::LevelViewer()
{
	//数字
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png");
	num->size = D3DXVECTOR3(70.0f, 70.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.80f, SCREEN_HEIGHT / 10 * 1.30f, 0.0f);
	num->SetColor(SET_COLOR_NOT_COLORED);
	num->intervalNumberScr = 65.0f;
	num->intervalNumberTex = 0.1f;
	num->placeMax = 4;
	num->baseNumber = 10;
	num->MakeVertex();

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/BG.png");
	bg->size = D3DXVECTOR3(125.0f, 125.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);
	bg->MakeVertex();

	//円ゲージ
	circleGuage = new CircleGauge(D3DXVECTOR2(125.0f, 125.0f));
	circleGuage->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
	circleGuage->SetScale(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	circleGuage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	circleGuage->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f));
	circleGuage->SetFillStart(circleGuage->Top);

	//矢印
	arrow = new RotateViewerDrawer();
	arrow->size = D3DXVECTOR3(12.0f, 20.0f, 0.0f);
	arrow->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	arrow->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.2f, SCREEN_HEIGHT / 10 * 2.0f, 0.0f);
	arrow->SetColor(SET_COLOR_NOT_COLORED);
	arrow->MakeVertex();

	//コンテナに矢印のテクスチャ情報をロードする
	for (int i = 0; i < typeMax; i++)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		LPDIRECT3DTEXTURE9 tex;

		D3DXCreateTextureFromFile(pDevice,
			arrowTexPath[i],
			&tex);

		arrowTexContainer.push_back(tex);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
LevelViewer::~LevelViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(bg);
	SAFE_DELETE(circleGuage);
	SAFE_DELETE(arrow);
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

	//矢印上下処理
	UpDownArrow();

	//前フレームのパラメータとしてセット
	lastParam[LevelAI] = (int)parameterBox[LevelAI];
}

//=============================================================================
// 描画処理
//=============================================================================
void LevelViewer::Draw(void)
{
	//背景を先に描画
	bg->SetVertex();
	bg->Draw();

	//円ゲージ
	circleGuage->SetPercent(drawingRatioLevel);
	circleGuage->Draw();

	//数宇
	num->DrawCounter(num->baseNumber, (int)parameterBox[LevelAI], num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);

	//*詳しい仕様が固まるまで矢印は描画しないでおく

	//if (isArrowPlaying)
	//{
	//	//矢印
	//	arrow->SetVertex();
	//	arrow->Draw();
	//}
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
			isArrowPlaying = false;
		}
		isLevelAI_Increasing = true;
		SetArrow(LevelUp);
	}

	//描画用RatioLevel増加
	IncreaseDrawingRatioLevel();

	//前フレームのLevelより現在のLevelAIが小さい場合
	if (currentParam[LevelAI] - lastParam[LevelAI] < 0)
	{
		if (isLevelAI_Increasing)
		{
			isLevelAI_Increasing = false;
			isArrowPlaying = false;
		}

		isLevelAI_Decreasing = true;
		SetArrow(LevelDown);
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
			isArrowPlaying = false;
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
	const float ratioDecreaseSpeed = 0.005f;

	//描画用RatioLevelの方がRatioLevelより大きい間、描画用RatioLevelを減少
	if (drawingRatioLevel > parameterBox[RatioLevel])
	{
		drawingRatioLevel -= ratioDecreaseSpeed;
		if (drawingRatioLevel <= parameterBox[RatioLevel])
		{
			drawingRatioLevel = parameterBox[RatioLevel];
			isLevelAI_Decreasing = false;
			isArrowPlaying = false;
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
// 矢印の上下処理
//=============================================================================
void LevelViewer::UpDownArrow()
{
	float initPosY = SCREEN_HEIGHT / 10 * 2.0f;

	if (isArrowPlaying)
	{
		float hopSpeed = 0.2f;
		float hopValue = 5.0f;

		if (isLevelAI_Increasing)
		{
			arrow->position.y -= (hopValue * sinf(radian));
		}
		if (isLevelAI_Decreasing)
		{
			arrow->position.y += (hopValue * sinf(radian));
		}

		if (radian >= D3DX_PI * 2)
		{
			radian = 0.0f;
		}
		radian += hopSpeed;
	}
	else
	{
		arrow->position.y = initPosY;
		radian = 0.0f;
	}
}

//=============================================================================
// 矢印のテクスチャ情報受け渡し処理
//=============================================================================
void LevelViewer::PassArrowTexture(ArrowID id)
{
	arrow->texture = arrowTexContainer[id];
}

//=============================================================================
// 矢印のセット処理
//=============================================================================
void LevelViewer::SetArrow(ArrowID id)
{
	PassArrowTexture(id);
	isArrowPlaying = true;
}
