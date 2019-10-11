//=============================================================================
//
// AIレベルビュアー処理 [LevelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LEVEL_VIEWER_H_
#define _LEVEL_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CountViewerDrawer;
class CircleGauge;
class GameViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class LevelViewer :public BaseViewer
{
public:
	LevelViewer();
	~LevelViewer();

	void Update(void);
	void Draw(void);

private:
	CircleGauge *circleGuage;
	CountViewerDrawer *num;
	GameViewer *gameViewer;

	void UpdateParam(void);
};

#endif