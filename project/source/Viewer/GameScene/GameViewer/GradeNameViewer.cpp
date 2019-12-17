//=============================================================================
//
// グレードネームクラス [GradeNameViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "GradeNameViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../../Sound/SoundConfig.h"
#include "../../../../Framework/Sound/SoundEffect.h"

const D3DXVECTOR3 TitleDefaultPos = D3DXVECTOR3(-350.0f, SCREEN_CENTER_Y - 80.0f, 0.0f);


//=============================================================================
// コンストラクタ
//=============================================================================
GradeNameViewer::GradeNameViewer(void) :
	Callback(nullptr)
{
	isPlaying = true;

	GradeTitle = new TextureDrawer(D3DXVECTOR2(600.0f, 600.0f), 1, 3);
	GradeTitle->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/GradeName.png");
	GradeTitle->SetPosition(TitleDefaultPos);
	GradeTitle->SetIndex(0);

	LineTex = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 540.0f), false);
	LineTex->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/GradeLine.png");
	LineTex->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
}

//=============================================================================
// デストラクタ
//=============================================================================
GradeNameViewer::~GradeNameViewer()
{
	SAFE_DELETE(GradeTitle);
	SAFE_DELETE(LineTex);
}

//=============================================================================
// 更新
//=============================================================================
void GradeNameViewer::Update()
{
	if (!isPlaying)
		return;

	GradeTitle->Update();
	LineTex->Update();
}

//=============================================================================
// 描画
//=============================================================================
void GradeNameViewer::Draw()
{
	if (!isPlaying)
		return;

	GradeTitle->Draw();
	LineTex->Draw();
}

//=============================================================================
// グレードネームを設置
//=============================================================================
void GradeNameViewer::SetGradeName(int fieldLevel, std::function<void(void)> callback)
{
	Callback = callback;
	isPlaying = true;

	LineTex->Expand(30.0f, ExpandType::LeftToRight, EaseType::OutCubic);

	// 初期化
	GradeTitle->SetPosition(TitleDefaultPos);
	GradeTitle->SetAlpha(0.0f);
	GradeTitle->SetIndex(fieldLevel);

	GradeTitle->Move(30.0f, D3DXVECTOR3(300.0f, SCREEN_CENTER_Y - 80.0f, 0.0f), EaseType::OutQuart);

	GradeTitle->Fade(30.0f, 1.0f);

	SE::Play(SoundConfig::SEID::NewField, 0.2f);

	TaskManager::Instance()->CreateDelayedTask(90, [&]()
	{
		GradeNameFade();
	});
}

//=============================================================================
// グレードネームのフェイドアウトを設置
//=============================================================================
void GradeNameViewer::GradeNameFade(void)
{
	LineTex->Close(30.0f, CloseType::CloseLeftToRight, EaseType::InCubic);

	GradeTitle->Move(30.0f, TitleDefaultPos, EaseType::InQuart);
	GradeTitle->Fade(30.0f, 0.0f, [&]()
	{
		isPlaying = false;
		if (Callback != nullptr)
			Callback();
	});
}
