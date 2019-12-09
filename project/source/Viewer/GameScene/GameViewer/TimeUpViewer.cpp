//=====================================
//
//TimeUpViewer.cpp
//機能:タイムアップビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TimeUpViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"

/**************************************
コンストラクタ
***************************************/
TimeUpViewer::TimeUpViewer() :
	cntFrame(0),
	active(false),
	callback(nullptr)
{
	tex = new TextureDrawer({ 800.0f, 200.0f }, false);
	tex->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	tex->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimeUpViewer/timeup.png");
}

/**************************************
デストラクタ
***************************************/
TimeUpViewer::~TimeUpViewer()
{
	SAFE_DELETE(tex);
}

/**************************************
更新処理
***************************************/
void TimeUpViewer::Update()
{
	if (!active)
		return;

	cntFrame++;

	//表示時間
	const int FrameFinish = 90;
	if (cntFrame == FrameFinish)
	{
		tex->Close(15, CloseType::FromLeftRight, EaseType::OutCubic, [&]()
		{
			active = false;
			tex->SetVisible(false);

			if(callback != nullptr)
				callback();
		});
	}

	tex->Update();
}

/**************************************
描画処理
***************************************/
void TimeUpViewer::Draw()
{
	tex->Draw();
}

/**************************************
セット処理
***************************************/
void TimeUpViewer::Set(std::function<void()> callback)
{
	cntFrame = 0;
	active = true;
	tex->Expand(15, ExpandType::ToLeftRight, EaseType::OutCubic);
	tex->SetVisible(true);
	this->callback = callback;
}
