//=============================================================================
//
// ビュアーにアニメーションをつける処理 [ViewerAnimater.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _VIEWER_ANIMATER_H_
#define _VIEWER_ANIMATER_H_

#include <functional>

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
	static void PlayAnim(std::vector <std::function<void()>> animArray, std::function<void()> Callback = nullptr);

	//移動処理
	static void Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type);

	//移動処理
	static void Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& end, float duration, EaseType type);

	//スケール処理
	static void Scale(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type);

	//フェード処理
	static void Fade(BaseViewerDrawer& viewer, const float& start, const float& end, float duration, EaseType type);

	//待機処理
	static void Wait(float duration);

private:

	//フレームカウント
	static int frameCnt;

	//アニメーション時間
	static float animTime;

	//アニメーション終了カウント
	static int finishedCnt;

	//アニメーションが終了したか
	static bool isFinished;

};
#endif