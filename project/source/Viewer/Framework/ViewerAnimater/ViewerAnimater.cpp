//=============================================================================
//
// ビュアーにアニメーションをつける処理 [ViewerAnimater.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../ViewerDrawer/BaseViewerDrawer.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "ViewerAnimater.h"

//=============================================================================
// コンストラクタ
//=============================================================================
ViewerAnimater::ViewerAnimater():
	frameCnt(0),
	animTime(0),
	finishedCnt(0),
	isFinished(false)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
ViewerAnimater::~ViewerAnimater()
{
	this->animArray.clear();
}

//=============================================================================
// アニメーション再生処理
//=============================================================================
void ViewerAnimater::PlayAnim(std::function<void()> Callback)
{
	//未終了状態に移行
	isFinished = false;

	//配列の中のアニメーションを実行
	this->animArray[finishedCnt]();

	//終了したら終了カウントをカウントアップ
	if (isFinished)
		finishedCnt++;

	//終了した回数がアニメーション数に達したら
	if (finishedCnt == this->animArray.size())
	{
		finishedCnt = 0;
		SetAnimFinished();

		//終了通知
		if (Callback) Callback();
	}
}

//=============================================================================
// 振動処理
//=============================================================================
void ViewerAnimater::Shake(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, float duration, std::function<void()> Callback)
{
	//何回振動させるか
	const int shakeNum = 400;
	//どのくらいの振れ幅か
	const float shakeValue = 3.0f;

	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	float radian = Easing::EaseValue(animTime, 0.0f, D3DX_PI * shakeNum, OutCirc);

	viewer.position.x = start.x + shakeValue * sinf(radian);

	//終了処理
	if (frameCnt < duration) return;
	viewer.position.x = start.x;
	SetAnimFinished();
}

//=============================================================================
// ホッピング処理
//=============================================================================
void ViewerAnimater::Hop(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, const D3DXVECTOR2 & value, float duration,std::function<void()> Callback)
{
	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	if (frameCnt <= duration/2) 
	viewer.size.y = Easing::EaseValue(animTime*2, start.y, start.y + value.y, OutCubic);
	else
	{
		viewer.size.y = Easing::EaseValue(animTime * 2, start.y + value.y, start.y, OutCubic);
	}

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// 移動処理（同時実行アニメーションあり）
//=============================================================================
void ViewerAnimater::Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start,
	const D3DXVECTOR2& end, float duration, EaseType type, std::function<void()> Callback)
{
	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	viewer.position.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// 移動処理（同時実行アニメーションあり）
//=============================================================================
void ViewerAnimater::MovePos(D3DXVECTOR2 & position, const D3DXVECTOR2 & start, const D3DXVECTOR2 & end, float duration, EaseType type, std::function<void()> Callback)
{
	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	position.x = Easing::EaseValue(animTime, start.x, end.x, type);
	position.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// スケール処理（同時実行アニメーションあり）
//=============================================================================
void ViewerAnimater::Scale(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start,
	const D3DXVECTOR2 & end, float duration, EaseType type, std::function<void()> Callback)
{
	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	viewer.size.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.size.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// フェード処理（同時実行アニメーションあり）
//=============================================================================
void ViewerAnimater::Fade(BaseViewerDrawer & viewer, const float & start,
	const float & end, float duration, EaseType type, std::function<void()> Callback)
{
	//フレームカウントと時間を更新
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	float alpha = Easing::EaseValue(animTime, start, end, type);
	viewer.SetAlpha(alpha);

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// 待機処理（同時実行アニメーションあり）
//=============================================================================
void ViewerAnimater::Wait(float duration, std::function<void()> Callback)
{
	//フレーム更新
	frameCnt++;

	if (Callback) Callback();

	//終了処理
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
//	移動処理（サブ）
//=============================================================================
void ViewerAnimater::SubMove(BaseViewerDrawer& viewer, const D3DXVECTOR2& start,
	const D3DXVECTOR2& end, EaseType type, std::function<void()> Callback)
{
	if (Callback) Callback();

	viewer.position.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);
}

//=============================================================================
// スケール処理（サブ）
//=============================================================================
void ViewerAnimater::SubScale(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start,
	const D3DXVECTOR2 & end, EaseType type, std::function<void()> Callback)
{
	if (Callback) Callback();

	viewer.size.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.size.y = Easing::EaseValue(animTime, start.y, end.y, type);
}

//=============================================================================
// フェード処理（サブ）
//=============================================================================
void ViewerAnimater::SubFade(BaseViewerDrawer & viewer, const float & start, const float & end, 
	const float maltiValue, EaseType type, std::function<void()> Callback)
{
	if (Callback) Callback();

	float alpha = Easing::EaseValue(animTime*maltiValue, start, end, type);
	viewer.SetAlpha(alpha);
}

//=============================================================================
// テキストフェード処理（サブ）
//=============================================================================
void ViewerAnimater::SubFadeText(TextViewer &text, const float & start, const float & end, const float maltiValue, EaseType type, std::function<void()> Callback)
{
	if (Callback) Callback();

	float alpha = Easing::EaseValue(animTime*maltiValue, start, end, type);
	text.SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f,alpha));
}

//=============================================================================
// ホッピング処理（サブ）
//=============================================================================
void ViewerAnimater::SubHop(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, 
	const D3DXVECTOR2 & value, float duration, std::function<void()> Callback)
{
	if (Callback) Callback();

	if (frameCnt <= duration / 2)
		viewer.size.y = Easing::EaseValue(animTime * 2, start.y, start.y + value.y, OutCubic);
	else
	{
		viewer.size.y = Easing::EaseValue(animTime * 2, start.y + value.y, start.y, OutCubic);
	}
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
// アニメーション終了処理（private）
//=============================================================================
void ViewerAnimater::SetAnimFinished(void)
{
	frameCnt = 0;
	animTime = 0;

	//終了状態に移行
	isFinished = true;
}

//=============================================================================
// アニメーション動作設定処理
//=============================================================================
void ViewerAnimater::SetAnimBehavior(std::vector<std::function<void()>> animArray)
{
	for (unsigned int i = 0; i < animArray.size(); i++)
	{
		this->animArray.push_back(animArray[i]);
	}
}

//=============================================================================
// アニメーション終了処理（public）
//=============================================================================
void ViewerAnimater::SetPlayFinished(bool& isPlayng, std::function<void()> Callback)
{
	isPlayng = false;
	if (Callback) Callback();
}

//=============================================================================
// アニメーションリセット処理
//=============================================================================
void ViewerAnimater::ResetAnim(void)
{
	frameCnt = 0;
	animTime = 0;
	finishedCnt = 0;
	isFinished = false;
}
