
//=============================================================================
//
// 連打ゲームゲージビュアー処理 [BeatGaugeViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_GAUGE_VIEWER_H_
#define _BEAT_GAUGE_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

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

	//震わせる
	void Shake(void);

	//再生中かどうか
	bool isPlaying;

	//フレームカウント
	int countFrame;

	//アニメーション時間
	float animTime;

	//ゲージパーセント
	float gaugePer;

	//ゲージバー描画処理
	void DrawBar(void);
};

#endif