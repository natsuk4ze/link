//=============================================================================
//
// 連打ゲームタイマービュアー処理 [BeatTimerViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_TIMER_VIEWER_H_
#define _BEAT_TIMER_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatTimerViewer :public BaseViewer
{
public:
	BeatTimerViewer();
	~BeatTimerViewer();

	void Update(void);
	void Draw(void);
	void Set(float time);

private:

	//前のテキスト(”あと”)
	BaseViewerDrawer * frontText;

	//後ろのテキスト(”秒”)
	BaseViewerDrawer * backText;

	//小数点
	BaseViewerDrawer *point;

	//少数部
	CountViewerDrawer *fewNum;

	//整数部
	CountViewerDrawer *intNum;

	//時間
	float time;
};

#endif