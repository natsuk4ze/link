//=============================================================================
//
// リンクレベルアップビュアー処理 [LinkLevelUpViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "LinkLevelUpViewer.h"

#include "../../../../main.h"
#include <string>
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
LinkLevelUpViewer::LinkLevelUpViewer() :
	Callback(nullptr)
{
	//テキスト
	text = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT / 3 * 2), 
		D3DXVECTOR2(750.0f, 140.0f),"data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Text.png");
	text->SetAlpha(0.0f);

	//月桂樹
	laurel = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT / 2 / 1.5),
		D3DXVECTOR2(300.0f, 300.0f), "data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Laurel.png");
	laurel->SetAlpha(0.0f);

	//数字
	num = new CountViewerDrawer(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT / 2 / 1.5),
		D3DXVECTOR2(0.0f, 0.0f), "data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Number.png",
		70.0f, 0.1f, 2);
	num->SetAlpha(0.0f);

	//＋
	plus = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_CENTER_X - num->intervalPosScr, SCREEN_HEIGHT / 2 / 1.5), 
		D3DXVECTOR2(100.0f, 100.0f), "data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Plus.png");
	plus->SetAlpha(0.0f);

	//アニメーション
	for (int i = 0; i < AnimLayer::Max; i++)
	{
		anim[i] = new ViewerAnimater();
	}

	std::vector<std::function<void()>> textVec = {
	[=] {
		//テキストをスクリーンイン
		anim[Text]->Move(*text, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT / 3 * 2), D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), 15.0f, OutCubic,[=]
		{
			//サブアニメーションでフェードイン
			anim[Text]->SubFade(*text, 0.0f, 1.0f,0.50f,OutCirc);
		});
	},
	[=] {
		//テキスト待機
		anim[Text]->Wait(30.0f);
	},
	[=] {
		//テキストをスクリーンアウト
		anim[Text]->Move(*text, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT/3), 15.0f, InCubic,[=]
		{
			//サブアニメーションでフェードアウト
			anim[Text]->SubFade(*text, 1.0f, 0.0f,1.0f,InCubic);
		});
	} };

	std::vector<std::function<void()>> bgVec = {
	[=] {
		//数字をスケール
		anim[BG]->Scale(*num,D3DXVECTOR2(0.0f, 0.0f),D3DXVECTOR2(100.0f, 100.0f),15.0f,OutBack,[=]
		{
			//背景出現
			AppearBG();
		});
	},
	[=]{
		//待機
		anim[BG]->Wait(45.0f,[=]
		{
			//背景消失
			DisAppearBG();
		});
	}
	};

	anim[Text]->SetAnimBehavior(textVec);
	anim[BG]->SetAnimBehavior(bgVec);
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
	for (int i = 0; i < AnimLayer::Max; i++)
	{
		SAFE_DELETE(anim[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void LinkLevelUpViewer::Update()
{
	if (!isPlaying) return;

	//アニメーション再生
	anim[Text]->PlayAnim([=]
	{
		anim[Text]->SetPlayFinished(isPlaying, Callback);
	});
	anim[BG]->PlayAnim(nullptr);
}

//=============================================================================
// 描画処理
//=============================================================================
void LinkLevelUpViewer::Draw(void)
{
	//再生中なら描画
	if (!isPlaying) return;

	//月桂樹を先に描画
	laurel->Draw();

	//数宇（0を描画しないでおく）
	num->DrawCounter(num->baseNumber, parameterBox,
		num->intervalPosScr, num->intervalPosTex);

	//＋
	plus->Draw();
	
	//テキスト
	text->Draw();
}

//=============================================================================
// 背景出現処理
//=============================================================================
void LinkLevelUpViewer::AppearBG()
{
	anim[BG]->SubFade(*plus, 0.0f, 1.0f, 0.30f, OutBack);
	anim[BG]->SubFade(*laurel, 0.0f, 1.0f, 0.30f, OutBack);
	anim[BG]->SubFade(*num, 0.0f, 1.0f, 0.30f, OutBack);
}

//=============================================================================
// 背景消失処理
//=============================================================================
void LinkLevelUpViewer::DisAppearBG()
{
	anim[BG]->SubFade(*plus, 1.0f, 0.0f, 0.30f, OutBack);
	anim[BG]->SubFade(*laurel, 1.0f, 0.0f, 0.30f, OutBack);
	anim[BG]->SubFade(*num, 1.0f, 0.0f, 0.30f, OutBack);
}

//=============================================================================
// 数字の桁数に応じて＋の位置と数字の位置を調整する処理
//=============================================================================
void LinkLevelUpViewer::SetNumPos(int level)
{
	int digit = std::to_string(level).length();

	num->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X + num->intervalPosScr/2*(digit-1), SCREEN_HEIGHT / 2 / 1.5, 0.0f));
	plus->SetPosition(D3DXVECTOR3((SCREEN_CENTER_X - num->intervalPosScr) - num->intervalPosScr/2*(digit-1), SCREEN_HEIGHT / 2 / 1.5, 0.0f));
}

//=============================================================================
// リンクレベルアップビュアーセット処理
//=============================================================================
void LinkLevelUpViewer::Set(int level, std::function<void()> callback)
{
	//パラメータを受け取る
	parameterBox = level;

	for (int i = 0; i < AnimLayer::Max; i++)
	{
		anim[i]->ResetAnim();
	}
	SetNumPos(level);

	//再生状態にする
	isPlaying = true;

	this->Callback = callback;
}