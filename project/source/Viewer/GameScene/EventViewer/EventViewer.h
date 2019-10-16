//=============================================================================
//
// イベントビュアー管理処理 [EventViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_VIEWER_H_
#define _EVENT_VIEWER_H_

#include <vector>

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

	std::vector <BaseViewer*> eventViewer;

private:
	int eventViewerMax;

	EventTelop * eventTelop;
	EventMessage *eventMessage;
};

#endif

