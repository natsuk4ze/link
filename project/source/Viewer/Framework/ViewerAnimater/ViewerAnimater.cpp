//=============================================================================
//
// ビュアーにアニメーションをつける処理 [ViewerAnimater.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../ViewerDrawer/BaseViewerDrawer.h"
#include "ViewerAnimater.h"

//=============================================================================
// static変数
//=============================================================================
int ViewerAnimater::finishedCnt = 0;
int ViewerAnimater::frameCnt = 0;
float ViewerAnimater::animTime = 0;
bool ViewerAnimater::isFinished = false;

//=============================================================================
// コンストラクタ
//=============================================================================
ViewerAnimater::ViewerAnimater()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
ViewerAnimater::~ViewerAnimater()
{
}

//=============================================================================
// アニメーション再生処理
//=============================================================================
void ViewerAnimater::PlayAnim(std::vector <std::function<void()>> animArray, std::function<void()> Callback)
{
	//未終了状態に移行
	isFinished = false;

	animArray[finishedCnt]();

	if (isFinished)
		finishedCnt++;

	//終了した回数がアニメーション数に達したら
	if (finishedCnt == animArray.size())
	{
		finishedCnt = 0;
		animArray.clear();
		//終了通知
		Callback();
	}
}

//=============================================================================
// 移動処理
//=============================================================================
void ViewerAnimater::Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start,
	const D3DXVECTOR2& end, float duration, EaseType type)
{
	//フレーム更新
	frameCnt++;

	//時間更新
	animTime = frameCnt / duration;

	viewer.position.x =  Easing::EaseValue(animTime,start.x,end.x,type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//終了
	if (frameCnt == duration)
	{
		frameCnt = 0;
		animTime = 0;
		//終了状態に移行
		isFinished = true;
	}
}

//=============================================================================
// 移動処理
//=============================================================================
void ViewerAnimater::Move(BaseViewerDrawer& viewer,
	const D3DXVECTOR2& end, float duration, EaseType type)
{
	//フレーム更新
	frameCnt++;

	//時間更新
	animTime = frameCnt / duration;

	const D3DXVECTOR2 start = D3DXVECTOR2(viewer.position.x, viewer.position.y);

	viewer.position.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//終了
	if (frameCnt == duration)
	{
		frameCnt = 0;
		animTime = 0;
		//終了状態に移行
		isFinished = true;
	}
}

//=============================================================================
// スケール処理
//=============================================================================
void ViewerAnimater::Scale(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, 
	const D3DXVECTOR2 & end, float duration, EaseType type)
{
	//フレーム更新
	frameCnt++;

	//時間更新
	animTime = frameCnt / duration;

	viewer.size.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.size.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//終了
	if (frameCnt == duration)
	{
		frameCnt = 0;
		animTime = 0;
		//終了状態に移行
		isFinished = true;
	}
}

//=============================================================================
// フェード処理
//=============================================================================
void ViewerAnimater::Fade(BaseViewerDrawer & viewer, const float & start, 
	const float & end, float duration, EaseType type)
{
	//フレーム更新
	frameCnt++;

	//時間更新
	animTime = frameCnt / duration;

	float alpha = Easing::EaseValue(animTime, start, end, type);
	viewer.SetAlpha(alpha);

	//終了
	if (frameCnt == duration)
	{
		frameCnt = 0;
		animTime = 0;
		//終了状態に移行
		isFinished = true;
	}
}

//=============================================================================
// 待機処理
//=============================================================================
void ViewerAnimater::Wait(float duration)
{
	//フレーム更新
	frameCnt++;

	//終了
	if (frameCnt == duration)
	{
		frameCnt = 0;
		//終了状態に移行
		isFinished = true;
	}
}
