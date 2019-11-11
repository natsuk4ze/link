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
EventTelop::EventTelop() :
	currentAnim(0)
{
	//テキスト
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventTelop/Text/Text.png");
	text->size = D3DXVECTOR3(1024, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_WIDTH*1.5, SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	text->MakeVertex();

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventTelop/BG/BG.png");
	bg->size = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->MakeVertex();
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

	//テキスト
	text->Draw();
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
	float bgEasingGoal = 128.0f;

	//背景のYサイズを更新
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
	float bgEasingStart = 128.0f;
	float bgEasingGoal = 0.0f;

	//背景のYサイズを更新
	bg->size.y = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Close]);

	//bg->size.yの最小をbgEasingGoalに設定
	Math::WrapAround(bg->size.y, bgEasingGoal, bg->size.y);
}

//=============================================================================
// テクスチャ情報受け渡し処理
//=============================================================================
void EventTelop::PassTexture(TelopID id)
{
	//テキストのUVを変更
	text->SetTexture(1, Max, id);

	bool isNegative;

	if (id >= Meteorite)
	{
		isNegative = true;
	}
	else
	{
		isNegative = false;
	}

	//背景のUVを変更
	bg->SetTexture(1, 2, isNegative);
	bg->vertexWk[1].tex.x = 3.0f;
	bg->vertexWk[3].tex.x = 3.0f;
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
