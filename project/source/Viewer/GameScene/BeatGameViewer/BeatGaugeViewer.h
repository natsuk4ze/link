
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

	//ゲージバー描画処理
	void DrawBar(void);

	//震わせる
	void Shake(void);

	//振動制御処理
	void HandleShake(void);

	//震わせるべきか
	bool shouldShake;

	//フレームカウント
	int countFrame;

	//アニメーション時間
	float animTime;

	//ゲージパーセント
	float gaugePer;

	//現在フレームのパラメータ
	float currentParam;

	//前フレームのパラメータ
	float lastParam;

	//振動用のラジアン
	float radian;
};

#endif