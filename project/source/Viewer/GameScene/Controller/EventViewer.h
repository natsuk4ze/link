//=============================================================================
//
// イベントビュアー管理処理 [EventViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_VIEWER_H_
#define _EVENT_VIEWER_H_

#include <vector>
#include <string>
#include <functional>
#include "../EventViewer/EventTelop.h"
#include "../../../../Framework/Pattern/Delegate.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class EventTelop;
class EventMessage;
class SealItemStockViewer;
class EventViewerParam;
class BaseViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventViewer
{
public:
	EventViewer();
	~EventViewer();

	void Update(void);
	void Draw(void);

	//メッセージセット
	void SetEventMessage(const std::string message);

	//テロップをセット
	void SetEventTelop(EventTelop::TelopID id, std::function<void(void)> Callback = nullptr);

	//ストック封印のアイコンを設置する
	void SetBanIcon(std::function<bool(void)> getInPause);

	// イベントメッセージのクリア
	void MessageClear(void);

private:
	static const int messageMax = 5;

	std::vector <BaseViewer*> eventViewer;
	std::vector <std::string> messageContainer;

	EventTelop * eventTelop;
	EventMessage *eventMessage[messageMax];
	SealItemStockViewer *sealStockViewer;

	void CountMessage(void);
	void PlayMessage(void);

	//メッセージがセットされるとカウントアップするカウンター
	int messageSetCnt;
};

#endif

