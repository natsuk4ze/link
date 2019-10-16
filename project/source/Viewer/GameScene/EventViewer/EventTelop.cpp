//=============================================================================
//
// イベントテロップ処理 [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/TelopDrawer.h"
#include "../../../../Framework/Input/input.h"
#include"../../../../Framework/Math/Easing.h"
#include "EventTelop.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//テロップの種類数
const int EventTelop::typeMax;

//テキストのテクスチャパス
static const char *textTexPath[EventTelop::typeMax]
{
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/PositiveText01.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/PositiveText02.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/NegativeText01.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/NegativeText02.png",
};

//背景のテクスチャパス
static const char *bgTexPath[EventTelop::typeMax]
{
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/PositiveBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/PositiveBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/NegativeBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/NegativeBG.png",
};

//アニメーションの数
static const int animMax = 5;

//テキストアニメーション開始位置
static const float textStartPositionX[animMax] = {
	SCREEN_WIDTH*1.5,
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5
};

//テキストアニメーション終了位置
static const float textEndPositionX[animMax] = {
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5,
	-SCREEN_WIDTH * 1.5
};

//テキストアニメーション種類
static const EaseType textAnimType[animMax] = {
	InOutCubic,
	InOutCubic,
	InOutCubic,
	InOutCubic,
	InOutCubic
};

//テキストアニメーション間隔
static const float textAnimDuration[animMax] = {
	10,
	120,
	100,
	120,
	10
};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventTelop::EventTelop()
{
	for (int i = 0; i < typeMax; i++)
	{
		//テキスト
		text[i] = new TelopDrawer();
		text[i]->isActive = false;
		text[i]->LoadTexture(textTexPath[i]);
		text[i]->MakeVertexText();
		text[i]->size = D3DXVECTOR3(512, 128.0f, 0.0f);
		text[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		text[i]->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
		text[i]->SetColor(SET_COLOR_NOT_COLORED);

		//背景
		bg[i] = new TelopDrawer();
		bg[i]->isActive = false;
		bg[i]->percentage = 0.0f;
		bg[i]->LoadTexture(bgTexPath[i]);
		bg[i]->MakeVertexBG();
		bg[i]->size = D3DXVECTOR3(SCREEN_WIDTH / 2, 60.0f, 0.0f);
		bg[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg[i]->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
		bg[i]->SetColor(SET_COLOR_NOT_COLORED);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventTelop::~EventTelop()
{
	for (int i = 0; i < typeMax; i++)
	{
		SAFE_DELETE(text[i]);
		SAFE_DELETE(bg[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void EventTelop::Update(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		bg[i]->PlayBG();
		Play(i);
	}

	text[PositiveEvent01]->isActive = true;
	bg[PositiveEvent01]->isActive = true;

	if (Keyboard::GetTrigger(DIK_T))
	{
		text[PositiveEvent01]->isPlaying = true;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void EventTelop::Draw(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		//背景を先に描画
		if (bg[i]->isActive)
		{
			bg[i]->Draw();
			bg[i]->SetVertexBG(bg[i]->percentage);
		}

		if (text[i]->isActive)
		{
			text[i]->Draw();
			text[i]->SetVertex();
		}
	}
}

//=============================================================================
// テロップ再生処理
//=============================================================================
void EventTelop::Play(int i)
{
	//画面外へ初期化
	D3DXVECTOR3 initPos = D3DXVECTOR3(3000.0f, SCREEN_HEIGHT / 2, 0.0f);
	text[i]->position = initPos;

	if (text[i]->isPlaying)
	{
		if (text[i]->currentAnim == text[i]->WaitBG_Open && bg[i]->isBG_Openinig == false)
		{
			bg[i]->PlayBG_Open();
		}
		if (text[i]->currentAnim == text[i]->WaitBG_Close && bg[i]->isBG_Closing == false)
		{
			bg[i]->PlayBG_Close();
		}

		text[i]->countFrame++;

		text[i]->position.x = Easing::EaseValue(text[i]->GetCountObject(textAnimDuration[text[i]->currentAnim]),
			textStartPositionX[text[i]->currentAnim],
			textEndPositionX[text[i]->currentAnim],
			textAnimType[text[i]->currentAnim]);

		if (text[i]->countFrame == textAnimDuration[text[i]->currentAnim])
		{
			text[i]->countFrame = 0;
			text[i]->currentAnim++;
		}
		if (text[i]->currentAnim == animMax)
		{
			text[i]->countFrame = 0;
			text[i]->currentAnim = 0;
			text[i]->position = initPos;
			text[i]->isPlaying = false;
		}
	}
}

//=============================================================================
// テロップセット処理
//=============================================================================
void EventTelop::Set(TelopID id, DelegateBase<void>* onFinish)
{
	//アクティブにする
	text[id]->isActive = true;
	bg[id]->isActive = true;

	//テロップ再生終了通知
	onFinish;
}
