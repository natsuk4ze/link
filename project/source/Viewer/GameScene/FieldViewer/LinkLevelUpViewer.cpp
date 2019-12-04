//=============================================================================
//
// リンクレベルアップビュアー処理 [LinkLevelUpViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "LinkLevelUpViewer.h"

#include "../../../../main.h"
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
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Text.png");
	text->size = D3DXVECTOR3(750.0f, 140.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT / 3 * 2, 0.0f);
	text->MakeVertex();
	text->SetAlpha(0.0f);

	//月桂樹
	laurel = new BaseViewerDrawer();
	laurel->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Laurel.png");
	laurel->size = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	laurel->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	laurel->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/2/1.5, 0.0f);
	laurel->MakeVertex();
	laurel->SetAlpha(0.0f);

	//数字
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Number.png");
	num->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT / 2/1.5, 0.0f);
	num->intervalPosScr = 70.0f;
	num->intervalPosTex = 0.1f;
	num->placeMax = 2;
	num->baseNumber = 10;
	num->MakeVertex();
	num->SetAlpha(0.0f);

	//＋
	plus = new BaseViewerDrawer();
	plus->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Plus.png");
	plus->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	plus->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	plus->position = D3DXVECTOR3(SCREEN_CENTER_X - num->intervalPosScr, SCREEN_HEIGHT / 2 / 1.5, 0.0f);
	plus->MakeVertex();
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
	num->DrawCounterLeft(num->baseNumber, parameterBox,
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
	anim[BG]->SubFade(*plus, 0.0f, 1.0f, 0.50f, OutBack);
	anim[BG]->SubFade(*laurel, 0.0f, 1.0f, 0.50f, OutBack);
	anim[BG]->SubFade(*num, 0.0f, 1.0f, 0.50f, OutBack);
}

//=============================================================================
// 背景消失処理
//=============================================================================
void LinkLevelUpViewer::DisAppearBG()
{
	anim[BG]->SubFade(*plus, 1.0f, 0.0f, 0.50f, OutBack);
	anim[BG]->SubFade(*laurel, 1.0f, 0.0f, 0.50f, OutBack);
	anim[BG]->SubFade(*num, 1.0f, 0.0f, 0.50f, OutBack);
}

//=============================================================================
// リンクレベルアップビュアーセット処理
//=============================================================================
void LinkLevelUpViewer::Set(int level, std::function<void()> callback)
{
	//パラメータを受け取る
	parameterBox = level;

	anim[Text]->ResetAnim();
	anim[BG]->ResetAnim();

	//再生状態にする
	isPlaying = true;

	this->Callback = callback;
}