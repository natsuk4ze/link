//=============================================================================
//
// グレードアップクラス [GradeUpViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "GradeUpViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Task/TaskManager.h"

const D3DXVECTOR3 AILevelDefaultPos = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, 130.0f, 0.0f);
const D3DXVECTOR3 TextDefaultPos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT + 384.0f, 0.0f);
const float ScaleNum = 1.5f;

//=============================================================================
// コンストラクタ
//=============================================================================
GradeUpViewer::GradeUpViewer(void) :
	Callback(nullptr)
{
	isPlaying = true;

	GradeUpText = new TextureDrawer(D3DXVECTOR2(1024.0f, 384.0f));
	GradeUpText->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/GradeUp.png");
	GradeUpText->SetPosition(TextDefaultPos);
	GradeUpText->SetAlpha(0.0f);

	AILevelTex = new TextureDrawer(D3DXVECTOR2(250.0f, 250.0f), false);
	AILevelTex->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/AILevel.png");
	AILevelTex->SetPosition(AILevelDefaultPos);
	AILevelTex->SetScale(ScaleNum);
}

//=============================================================================
// デストラクタ
//=============================================================================
GradeUpViewer::~GradeUpViewer()
{
	SAFE_DELETE(GradeUpText);
	SAFE_DELETE(AILevelTex);
}

//=============================================================================
// 更新
//=============================================================================
void GradeUpViewer::Update()
{
	if (!isPlaying)
		return;

	GradeUpText->Update();
	AILevelTex->Update();
}

//=============================================================================
// 描画
//=============================================================================
void GradeUpViewer::Draw()
{
	if (!isPlaying)
		return;

	AILevelTex->Draw();
	GradeUpText->Draw();
}

//=============================================================================
// グレードアップ演出を設置
//=============================================================================
void GradeUpViewer::SetGradeUp(std::function<void(void)> callback)
{
	Callback = callback;
	isPlaying = true;

	// 初期化
	AILevelTex->SetVisible(true);
	AILevelTex->SetScale(1 / ScaleNum);
	AILevelTex->SetAlpha(1.0f);
	AILevelTex->SetPosition(AILevelDefaultPos);

	// 画面中央に移動しながら拡大
	AILevelTex->Move(60.0f, D3DXVECTOR3(SCREEN_CENTER_X, 284.0f, 0.0f), EaseType::OutCubic);
	AILevelTex->SetScale(60.0f, ScaleNum, EaseType::OutCubic, [&]()
	{
		TextPopUp();
	});

	TaskManager::Instance()->CreateDelayedTask(180, [&]()
	{
		GradeUpFadeOut();
	});
}

//=============================================================================
// テキストのポップアップ演出を設置
//=============================================================================
void GradeUpViewer::TextPopUp(void)
{
	// 初期化
	GradeUpText->SetAlpha(0.0f);
	GradeUpText->SetPosition(TextDefaultPos);

	// 画面中央に移動しながらフェイドイン
	GradeUpText->Fade(60.0f, 1.0f);
	GradeUpText->Move(60.0f, D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), EaseType::OutCubic);
}

//=============================================================================
// フェイドアウト演出を設置
//=============================================================================
void GradeUpViewer::GradeUpFadeOut()
{
	// 画面上方に移動しながらフェイドアウト
	GradeUpText->Move(60.0f, D3DXVECTOR3(SCREEN_CENTER_X, -384.0f, 0.0f), EaseType::OutCubic);
	GradeUpText->Fade(60.0f, 0.0f);

	// フェイドアウト
	AILevelTex->Fade(60.0f, 0.0f, [&]()
	{
		isPlaying = false;
		if (Callback != nullptr)
			Callback();
	});
}

