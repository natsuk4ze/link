//=============================================================================
//
// グレードフレームクラス [GradeFrameViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "GradeFrameViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Task/TaskManager.h"



//=============================================================================
// コンストラクタ
//=============================================================================
GradeFrameViewer::GradeFrameViewer(void) :
	Callback(nullptr)
{
	isPlaying = true;

	FrameUp = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 128.0f), false);
	FrameUp->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/GradeFrame.png");
	FrameUp->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 64.0f, 0.0f));

	FrameDown = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 128.0f), false);
	FrameDown->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/GradeFrame.png");
	FrameDown->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT - 64.0f, 0.0f));
}

//=============================================================================
// デストラクタ
//=============================================================================
GradeFrameViewer::~GradeFrameViewer()
{
	SAFE_DELETE(FrameUp);
	SAFE_DELETE(FrameDown);
}

//=============================================================================
// 更新
//=============================================================================
void GradeFrameViewer::Update()
{
	if (!isPlaying)
		return;

	FrameUp->Update();
	FrameDown->Update();
}

//=============================================================================
// 描画
//=============================================================================
void GradeFrameViewer::Draw()
{
	if (!isPlaying)
		return;

	FrameUp->Draw();
	FrameDown->Draw();
}

//=============================================================================
// スライドを設置する
//=============================================================================
void GradeFrameViewer::SlideIn(std::function<void(void)> callback)
{
	Callback = callback;

	FrameUp->Expand(15.0f, ExpandType::ExpandUpToDown);
	FrameDown->Expand(15.0f, ExpandType::ExpandDownToUp, EaseType::Linear, [&]()
	{
		if (Callback != nullptr)
			Callback();
	});
}


//=============================================================================
// スライドアウトを設置する
//=============================================================================
void GradeFrameViewer::SlideOut(std::function<void(void)> callback)
{
	Callback = callback;

	FrameUp->Close(15.0f, CloseType::CloseDownToUp);
	FrameDown->Close(15.0f, CloseType::CloseUpToDown, EaseType::Linear, [&]()
	{
		if (Callback != nullptr)
			Callback();
	});
}

