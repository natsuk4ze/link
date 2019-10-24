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
#include "EventTelop.h"
#include "../../../../Framework/Pattern/Delegate.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class EventTelop;
class EventMessage;
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
	void SetEventMessage(const std::string Message);
	//void SetEventTelop(TelopID id, Delegate<void(void)> *onFinish);
	void SetEventTelop(TelopID id, std::function<void(void)> FinishFunc = NULL);

	//テロップセット
	//void SetEventTelop(EventTelop::TelopID id, Delegate<void(void)> *onFinish);

	//メッセージがセットされるとカウントアップするカウンター
	int messageSetCnt;

private:
	static const int messageMax = 5;
	int eventViewerMax;

	std::vector <BaseViewer*> eventViewer;
	std::vector <int> messageContainer;

	EventTelop * eventTelop;
	EventMessage *eventMessage[messageMax];

	void CountMessage(void);

};

#endif

