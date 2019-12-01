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

	//配列の中のアニメーションを実行
	animArray[finishedCnt]();

	//終了したら終了カウントをカウントアップ
	if (isFinished)
		finishedCnt++;

	//終了した回数がアニメーション数に達したら
	if (finishedCnt == animArray.size())
	{
		finishedCnt = 0;
		SetAnimFinished();
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
	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	viewer.position.x =  Easing::EaseValue(animTime,start.x,end.x,type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// スケール処理
//=============================================================================
void ViewerAnimater::Scale(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, 
	const D3DXVECTOR2 & end, float duration, EaseType type)
{
	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	viewer.size.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.size.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// フェード処理
//=============================================================================
void ViewerAnimater::Fade(BaseViewerDrawer & viewer, const float & start, 
	const float & end, float duration, EaseType type)
{
	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	float alpha = Easing::EaseValue(animTime, start, end, type);
	viewer.SetAlpha(alpha);

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// 待機処理
//=============================================================================
void ViewerAnimater::Wait(float duration)
{
	//フレーム更新
	frameCnt++;

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// フレームカウントと時間の更新処理
//=============================================================================
void ViewerAnimater::UpdateFrameAndTime(float duration)
{
	//フレーム更新
	frameCnt++;

	//時間更新
	animTime = frameCnt / duration;
}

//=============================================================================
// アニメーション終了処理
//=============================================================================
void ViewerAnimater::SetAnimFinished(void)
{
	frameCnt = 0;
	animTime = 0;

	//終了状態に移行
	isFinished = true;
}
