//=============================================================================
//
// ストック使用不可イベントクラス [BanStockUseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BanStockUseEvent_H_
#define _BanStockUseEvent_H_

#include "../EventBase.h"
#include <functional>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BeatGame;
class EventViewer;
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BanStockUseEvent : public EventBase
{
private:
	int RemainTime;
	bool InDebuff;
	std::function<void(bool)> SetBanStock;

	// 連打ゲーム
	BeatGame *beatGame;
	BaseViewerDrawer *Viewer;


public:
	BanStockUseEvent(EventViewer* eventViewer, std::function<void(bool)> SetBanStock);
	~BanStockUseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void ReceiveBeatResult(bool IsSuccess);
	void CountdownStart(void);
	void EventOver(void);
};

#endif
