//=============================================================================
//
// 連打ゲーム結果ビュアー処理 [BeatResultViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "BeatResultViewer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//アニメーションの数
static const int animMax = 5;

//テキストアニメーション開始位置
static const float textStartPositionX[animMax] = {
	SCREEN_WIDTH*1.5,
	-SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	+SCREEN_WIDTH * 1.5
};

//テキストアニメーション終了位置
static const float textEndPositionX[animMax] = {
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	+SCREEN_WIDTH * 1.5,
	+SCREEN_WIDTH * 1.5
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
BeatResultViewer::BeatResultViewer() :
	currentAnim(0)
{
	//テキスト
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatResultViewer/Text.png");
	text->size = D3DXVECTOR3(1024, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(-SCREEN_WIDTH*1.5, SCREEN_CENTER_Y, 0.0f);
	text->MakeVertex();

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatResultViewer/BG.png");
	bg->size = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	bg->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BeatResultViewer::~BeatResultViewer()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// 更新処理
//=============================================================================
void BeatResultViewer::Update()
{
	//テロップ再生処理
	Play();
}

//=============================================================================
// 描画処理
//=============================================================================
void BeatResultViewer::Draw(void)
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
void BeatResultViewer::Play()
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
void BeatResultViewer::OpenBG(void)
{
	//イージングのスタートとゴールを設定
	float bgEasingStart = 0.0f;
	float bgEasingGoal = 128.0f;

	//背景のYサイズを更新
	bg->size.y = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Open]);
}

//=============================================================================
// 背景を閉じる処理
//=============================================================================
void BeatResultViewer::CloseBG(void)
{
	//イージングのスタートとゴールを設定
	float bgEasingStart = 128.0f;
	float bgEasingGoal = 0.0f;

	//背景のYサイズを更新
	bg->size.y = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Close]);
}

//=============================================================================
// テクスチャ情報受け渡し処理
//=============================================================================
void BeatResultViewer::PassTexture(ResultID id)
{
	//テキストのUVを変更
	text->SetTexture(1, ResultID::Max, id);

	//背景のUVを変更
	bg->SetTexture(1, ResultID::Max, id);
	bg->vertexWk[1].tex.x = 3.0f;
	bg->vertexWk[3].tex.x = 3.0f;
}

//=============================================================================
// 結果ビュアーセット処理
//=============================================================================
void BeatResultViewer::Set(ResultID id, std::function<void(void)> Callback)
{
	//テクスチャ情報受け渡し
	PassTexture(id);

	//再生状態にする
	isPlaying = true;

	//テロップ再生終了通知
	this->Callback = Callback;
}
