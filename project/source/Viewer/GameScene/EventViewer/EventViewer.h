//=============================================================================
//
// イベントビュアー管理処理 [EventViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_VIEWER_H_
#define _EVENT_VIEWER_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class EventTelop;
class EventMessage;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventViewer
{
public:
	EventViewer();
	~EventViewer();

	virtual void Update(void);
	virtual void Draw(void);

private:
	int eventViewerMax;

	EventTelop * eventTelop;
	EventMessage *eventMessage;
};

#endif

