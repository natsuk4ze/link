//=============================================================================
//
// 連打ゲームイベントクラス [BeatGame.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BeatGame_H_
#define _BeatGame_H_

#include "../EventBase.h"
#include <functional>
#include <string>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class EventViewer;
class BaseViewerDrawer;
class CountViewerDrawer;
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatGame : public EventBase
{
private:
	int RemainFrame;
	int InputCount;
	bool TelopOver;
	std::function<void(bool)> Callback;

	// テキスト
	TextViewer *Text;
	// 小数点
	BaseViewerDrawer *point;
	// 少数部
	CountViewerDrawer *fewNum;
	// 整数部
	CountViewerDrawer *intNum;

public:
	BeatGame(EventViewer* eventViewer, std::function<void(bool)> CallBack = nullptr);
	~BeatGame();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void CountdownStart(void);
};

#endif
