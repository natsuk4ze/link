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
class GameViewer;

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

private:
	BaseViewerDrawer *bg;
	CountViewerDrawer *num;
	GameViewer *gameViewer;

	void UpdateParam(void);
};

#endif