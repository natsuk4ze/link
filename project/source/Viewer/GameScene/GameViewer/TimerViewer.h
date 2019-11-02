//=============================================================================
//
// タイマービュアー処理 [TimerViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TIMER_VIEWER_H_
#define _TIMER_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class TimerViewer :public BaseViewer
{
public:
	TimerViewer();
	~TimerViewer();

	void Update(void);
	void Draw(void);

	//パラメータを受けとる箱
	float parameterBox;

private:

	//背景
	BaseViewerDrawer *bg;

	//小数点
	BaseViewerDrawer *point;

	//少数部
	CountViewerDrawer *fewNum;

	//整数部
	CountViewerDrawer *intNum;
};

#endif