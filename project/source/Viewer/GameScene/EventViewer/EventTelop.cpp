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
	//テキスト
	text = new TelopDrawer();
	text->MakeVertexText();
	text->size = D3DXVECTOR3(512, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	text->SetColor(SET_COLOR_NOT_COLORED);

	//背景
	bg = new TelopDrawer();
	bg->percentage = 0.0f;
	bg->MakeVertexBG();
	bg->size = D3DXVECTOR3(SCREEN_WIDTH / 2, 60.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//コンテナにテクスチャ情報をロードする
	for (int i = 0; i < typeMax; i++)
	{
		LPDIRECT3DTEXTURE9 tTex;
		LPDIRECT3DTEXTURE9 bgTex;

		D3DXCreateTextureFromFile(pDevice,
			textTexPath[i],
			&tTex);

		textTexContainer.push_back(tTex);

		D3DXCreateTextureFromFile(pDevice,
			bgTexPath[i],
			&bgTex);

		bgTexContainer.push_back(bgTex);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventTelop::~EventTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// 更新処理
//=============================================================================
void EventTelop::Update()
{
	bg->PlayBG();
	Play();

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_T))
	{
		Set(PositiveEvent01, onFinish);
	}

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void EventTelop::Draw(void)
{
	//背景を先に描画
	if (bg->isPlaying)
	{
		bg->Draw();
		bg->SetVertexBG(bg->percentage);
	}

	if (text->isPlaying)
	{
		text->Draw();
		text->SetVertex();
	}
}

//=============================================================================
// テロップ再生処理
//=============================================================================
void EventTelop::Play()
{
	//画面外へ初期化
	D3DXVECTOR3 initPos = D3DXVECTOR3(3000.0f, SCREEN_HEIGHT / 2, 0.0f);
	text->position = initPos;

	if (text->isPlaying&&bg->isPlaying)
	{
		if (text->currentAnim == text->WaitBG_Open && bg->isBG_Openinig == false)
		{
			bg->PlayBG_Open();
		}
		if (text->currentAnim == text->WaitBG_Close && bg->isBG_Closing == false)
		{
			bg->PlayBG_Close();
		}

		text->countFrame++;

		text->position.x = Easing::EaseValue(text->GetCountObject(textAnimDuration[text->currentAnim]),
			textStartPositionX[text->currentAnim],
			textEndPositionX[text->currentAnim],
			textAnimType[text->currentAnim]);

		if (text->countFrame == textAnimDuration[text->currentAnim])
		{
			text->countFrame = 0;
			text->currentAnim++;
		}
		if (text->currentAnim == animMax)
		{
			text->countFrame = 0;
			text->currentAnim = 0;
			text->position = initPos;
			text->isPlaying = false;
		}
		if (text->currentAnim > animMax)
		{
			bg->isPlaying = false;

			//再生終了の通知
			(*onFinish)();
		}
	}
}

//=============================================================================
// テクスチャ情報受け渡し処理
//=============================================================================
void EventTelop::PassTexture(TelopID id)
{
	text->texture = textTexContainer[id];
	bg->texture = bgTexContainer[id];
}

//=============================================================================
// テロップセット処理
//=============================================================================
void EventTelop::Set(TelopID id, DelegateBase<void>* onFinish)
{
	//テクスチャ情報受け渡し
	PassTexture(id);

	//再生状態にする
	text->isPlaying = true;
	bg->isPlaying = true;

	//テロップ再生終了通知
	this->onFinish = onFinish;
}
