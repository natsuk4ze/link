
//=============================================================================
//
// 連打ゲームゲージビュアー処理 [BeatGaugeViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_GAUGE_VIEWER_H_
#define _BEAT_GAUGE_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <functional>
#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class ViewerAnimater;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatGaugeViewer :public BaseViewer
{
public:
	BeatGaugeViewer();
	~BeatGaugeViewer();

	void Update();
	void Draw(void);
	void Set(float percent);

private:
	BaseViewerDrawer *bar;
	BaseViewerDrawer *frame;
	ViewerAnimater *anim;

	//ゲージバー描画処理
	void DrawBar(void);

	//アニメーションの動作を設定
	void SetAnimBehavior(void);

	//アニメーション終了
	bool SetPlayFinished(void);

	//再生中かどうか
	bool isPlaying;

	//ゲージパーセント
	float gaugePer;

	//アニメーション配列
	std::vector <std::function<void()>> animArray{1};
};

#endif