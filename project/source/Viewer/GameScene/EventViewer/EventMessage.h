
//=============================================================================
//
// イベントメッセージ処理 [EventMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_MESSAGE_H_
#define _EVENT_MESSAGE_H_

#include "../EventViewer/EventViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventMessage :public EventViewer
{
public:
	EventMessage();
	~EventMessage();

	void Update(void);
	void Draw(void);
	//void Set(const string message);

	bool isPlaying;

private:
	BaseViewerDrawer *bg;
	TextViewer *text;
};

#endif