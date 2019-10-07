//=============================================================================
//
// Gameシーンビュアー管理処理 [GameViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class StockViewer;
class TimerViewer;
class LevelViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GameViewer:public BaseViewer
{
public:
	GameViewer();
	~GameViewer();

	void Update(void);
	void Draw(void);

	void ReceiveParam();

private:
	int baseViewerMax;

	StockViewer *stockViewer;
	TimerViewer *timerViewer;
	LevelViewer *levelViewer;
};

#endif

