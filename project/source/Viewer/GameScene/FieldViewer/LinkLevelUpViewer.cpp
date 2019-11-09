//=============================================================================
//
// リンクレベルアップビュアー処理 [LinkLevelUpViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "LinkLevelUpViewer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//アニメーションの数
static const int animMax = 5;

//テキストアニメーション開始位置
static const float textStartPositionY[animMax] = {
	SCREEN_HEIGHT/3*2,
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_HEIGHT/3
};

//テキストアニメーション終了位置
static const float textEndPositionY[animMax] = {
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_HEIGHT/3,
	SCREEN_HEIGHT/3
};

//アニメーション種類
static const EaseType animType[animMax] = {
	OutCubic,
	OutBack,
	InOutCubic,
	InCubic,
	InOutCubic
};

//アニメーション間隔(ここを変更するとアニメーションの速さを調整できる)
//*注意(0を入れると無限大になるからアニメーションそのものを削除すること)
static const float animDuration[animMax] = {
	15,
	20,
	40,
	15,
	10
};

//アニメーションシーン
enum TelopAnimScene
{
	Text_FadeIn_PopIn,
	Num_Laurel_In,
	Wait,
	Text_FadeOut_PopOut,
	Num_Laurel_Out
};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
LinkLevelUpViewer::LinkLevelUpViewer()
{
	//テキスト
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Text.png");
	text->size = D3DXVECTOR3(750.0f, 100.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, textStartPositionY[0], 0.0f);
	text->MakeVertex();
	text->SetAlpha(0.0f);

	//月桂樹
	laurel = new BaseViewerDrawer();
	laurel->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Laurel.png");
	laurel->size = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	laurel->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	laurel->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/2/1.5, 0.0f);
	laurel->MakeVertex();

	//＋
	plus = new BaseViewerDrawer();
	plus->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Plus.png");
	plus->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	plus->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	plus->position = D3DXVECTOR3(SCREEN_CENTER_X-80.0f, SCREEN_HEIGHT / 2/1.5, 0.0f);
	plus->MakeVertex();

	//数字
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Number.png");
	num->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT / 2/1.5, 0.0f);
	num->intervalPosScr = 80.0f;
	num->intervalPosTex = 0.1f;
	num->placeMax = 2;
	num->baseNumber = 10;
	num->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
LinkLevelUpViewer::~LinkLevelUpViewer()
{
	SAFE_DELETE(text);
	SAFE_DELETE(laurel);
	SAFE_DELETE(plus);
	SAFE_DELETE(num);
}

//=============================================================================
// 更新処理
//=============================================================================
void LinkLevelUpViewer::Update()
{
	//ビュアー再生処理
	Play();
}

//=============================================================================
// 描画処理
//=============================================================================
void LinkLevelUpViewer::Draw(void)
{
	//再生中なら描画
	if (!isPlaying) return;

	if (currentAnim >= Num_Laurel_In)
	{
		//月桂樹を先に描画
		laurel->Draw();

		//数宇
		num->DrawCounter(num->baseNumber, parameterBox,num->placeMax,
			num->intervalPosScr, num->intervalPosTex);

		//＋
		plus->Draw();
	}

	//テキスト
	text->Draw();
}

//=============================================================================
// ビュアー再生処理
//=============================================================================
void LinkLevelUpViewer::Play()
{
	//再生中なら描画
	if (!isPlaying) return;

	//フレーム更新
	countFrame++;

	//時間更新
	animTime = countFrame / animDuration[currentAnim];

	//シーン毎に実行するサブアニメーション
	switch (currentAnim)
	{
	case(Text_FadeIn_PopIn):
		FadeInText();
		break;
	case(Text_FadeOut_PopOut):
		FadeOutText();
		break;
	case(Num_Laurel_In):
		InNum();
		break;
	default:
		break;
	}

	//ポジションを更新
	text->position.y = Easing::EaseValue(animTime,
		textStartPositionY[currentAnim],
		textEndPositionY[currentAnim],
		animType[currentAnim]);

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
		text->position.y = textStartPositionY[0];
		num->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		isPlaying = false;
	}
}

//=============================================================================
// テキストフェードイン処理
//=============================================================================
void LinkLevelUpViewer::FadeInText(void)
{
	//イージングのスタートとゴールを設定
	float easingStart = 0.0f;
	float easingGoal = 1.0f;

	//テクスチャのα値
	float alpha;

	alpha = Easing::EaseValue(animTime, easingStart, easingGoal, animType[Text_FadeIn_PopIn]);
	text->SetAlpha(alpha);
}

//=============================================================================
// テキストフェードアウト処理
//=============================================================================
void LinkLevelUpViewer::FadeOutText(void)
{
	//イージングのスタートとゴールを設定
	float easingStart = 1.0f;
	float easingGoal = 0.0f;

	//テクスチャのα値
	float alpha;

	alpha = Easing::EaseValue(animTime, easingStart, easingGoal, animType[Text_FadeOut_PopOut]);
	text->SetAlpha(alpha);
}

//=============================================================================
// 数字出現処理
//=============================================================================
void LinkLevelUpViewer::InNum()
{
	//イージングのスタートとゴールを設定
	float easingStart = 0.0f;
	float easingGoal = 120.0f;

	num->size.x = Easing::EaseValue(animTime, easingStart, easingGoal, animType[Num_Laurel_In]);
	num->size.y = Easing::EaseValue(animTime, easingStart, easingGoal, animType[Num_Laurel_In]);
}

//=============================================================================
// リンクレベルアップビュアーセット処理
//=============================================================================
void LinkLevelUpViewer::Set(int level)
{
	//パラメータを受け取る
	parameterBox = level;

	//再生状態にする
	isPlaying = true;
}
