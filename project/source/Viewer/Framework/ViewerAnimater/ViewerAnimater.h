//=============================================================================
//
// ビュアーにアニメーションをつける処理 [ViewerAnimater.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _VIEWER_ANIMATER_H_
#define _VIEWER_ANIMATER_H_

#include "../../../../main.h"
#include <functional>
#include "../../../../Framework/Math/Easing.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ViewerAnimater
{
public:
	ViewerAnimater();
	~ViewerAnimater();

	//アニメーション再生処理
	void PlayAnim(std::function<void()> Callback = nullptr);

	//移動処理
	void Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type);
	//スケール処理
	void Scale(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type);
	//フェード処理
	void Fade(BaseViewerDrawer& viewer, const float& start, const float& end, float duration, EaseType type);
	//振動処理
	void Shake(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, float duration);
	//待機処理
	void Wait(float duration);

	//*****************************************************************************
	// 以下、Callbackで同時に実行する処理を呼べるver.
	// ex)フェードアウトしながらスクリーンアウト...etc
	// 注意：Callbackでアニメーションを呼ぶ場合、Subを使うこと
	//*****************************************************************************

	//移動処理
	void Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type, std::function<void()> Callback);
	//スケール処理
	void Scale(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type, std::function<void()> Callback);
	//フェード処理
	void Fade(BaseViewerDrawer& viewer, const float& start, const float& end, float duration, EaseType type, std::function<void()> Callback);
	//待機処理
	void Wait(float duration, std::function<void()> Callback);

	//移動処理
	void SubMove(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, EaseType type);
	//スケール処理
	void SubScale(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, EaseType type);
	//フェード処理
	void SubFade(BaseViewerDrawer& viewer, const float& start, const float& end, const float maltiValue,EaseType type);

	//アニメーションの動作を設定
	void SetAnimBehavior(std::vector <std::function<void()>> animArray);

	//アニメーション終了処理
	void SetPlayFinished(bool& isPlayng, std::function<void()> Callback = nullptr);

	//アニメーションのリセット処理
	void ResetAnim(void);

private:

	//アニメーション終了処理
	void SetAnimFinished(void);

	//フレームカウントと時間を更新
	void UpdateFrameAndTime(float duration);

	//フレームカウント
	int frameCnt;

	//アニメーション時間
	float animTime;

	//アニメーション終了カウント
	int finishedCnt;

	//アニメーションが終了したか
	bool isFinished;

	//アニメーション配列
	std::vector <std::function<void()>> animArray;
};
#endif