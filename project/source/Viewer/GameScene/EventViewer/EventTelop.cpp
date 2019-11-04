//=============================================================================
//
// イベントテロップ処理 [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "EventTelop.h"

#ifdef _DEBUG

#include "../../../../Framework/Input/input.h"

#endif

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
	SCREEN_WIDTH*1.2,
	SCREEN_WIDTH*1.2,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.2
};

//テキストアニメーション終了位置
static const float textEndPositionX[animMax] = {
	SCREEN_WIDTH*1.2,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.2,
	-SCREEN_WIDTH * 1.2
};

//テキストアニメーション種類
static const EaseType animType[animMax] = {
	OutCirc,
	OutCirc,
	InOutCubic,
	InCirc,
	OutCirc
};

//テキストアニメーション間隔(ここを変更するとアニメーションの速さを調整できる)
//*注意(0を入れると無限大になるからアニメーションそのものを削除すること)
static const float animDuration[animMax] = {
	15,
	50,
	5,
	30,
	15
};

//アニメーションシーン
enum TelopAnimScene
{
	BG_Open,
	Text_In,
	Text_Stop,
	Text_Out,
	BG_Close
};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventTelop::EventTelop()
{
	//テキスト
	text = new BaseViewerDrawer();
	text->size = D3DXVECTOR3(512, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_WIDTH*1.2, SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	text->SetColor(SET_COLOR_NOT_COLORED);
	text->MakeVertex();

	//背景
	bg = new BaseViewerDrawer();
	bg->size = D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);
	bg->MakeVertex();

	//背景のUV座標を変更
	bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bg->vertexWk[1].tex = D3DXVECTOR2(3.0, 0.0f);
	bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bg->vertexWk[3].tex = D3DXVECTOR2(3.0f, 1.0f);

	//コンテナにテクスチャ情報をロードする
	for (int i = 0; i < typeMax; i++)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

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
	//テロップ再生処理
	Play();
}

//=============================================================================
// 描画処理
//=============================================================================
void EventTelop::Draw(void)
{
	//再生中なら描画
	if (!isPlaying) return;

	//背景を先に描画
	bg->Draw();
	bg->SetVertex();

	//テキスト
	text->Draw();
	text->SetVertex();
}

//=============================================================================
// テロップ再生処理
//=============================================================================
void EventTelop::Play()
{
	//再生中なら描画
	if (!isPlaying) return;

	//フレーム更新
	countFrame++;

	//時間更新
	animTime = countFrame / animDuration[currentAnim];

	//アニメーションシーンがBG_Openの間背景をオープンする
	if (currentAnim == BG_Open)
	{
		OpenBG();
	}

	//ポジションを更新
	text->position.x = Easing::EaseValue(animTime,
		textStartPositionX[currentAnim],
		textEndPositionX[currentAnim],
		animType[currentAnim]);

	//アニメーションシーンがBG_Closeの間背景をクローズする
	if (currentAnim == BG_Close)
	{
		CloseBG();
	}

	//アニメーション更新
	if (countFrame == animDuration[currentAnim])
	{
		countFrame = 0;
		currentAnim++;
	}

	//アニメーション終了
	if (currentAnim >= animMax)
	{
		countFrame = 0;
		currentAnim = 0;
		isPlaying = false;

		//ヌルチェック
		if (Callback != nullptr)
		{
			//再生終了の通知
			Callback();
		}
	}
}

//=============================================================================
// 背景を開く処理
//=============================================================================
void EventTelop::OpenBG(void)
{
	//イージングのスタートとゴールを設定
	float bgEasingStart = 0.0f;
	float bgEasingGoal = 60.0f;

	//背景アクティブパーセンテージを更新
	bg->size.y = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Open]);

	//bg->size.yの最大をbgEasingGoalに設定
	Math::WrapAround(bg->size.y, bgEasingGoal, bg->size.y);
}

//=============================================================================
// 背景を閉じる処理
//=============================================================================
void EventTelop::CloseBG(void)
{
	//イージングのスタートとゴールを設定
	float bgEasingStart = 60.0f;
	float bgEasingGoal = 0.0f;

	//背景アクティブパーセンテージを更新
	bg->size.y = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Close]);

	//bg->size.yの最小をbgEasingGoalに設定
	Math::WrapAround(bg->size.y, bgEasingGoal, bg->size.y);
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
void EventTelop::Set(TelopID id, std::function<void(void)> Callback)
{
	//テクスチャ情報受け渡し
	PassTexture(id);

	//再生状態にする
	isPlaying = true;

	//テロップ再生終了通知
	this->Callback = Callback;
}
