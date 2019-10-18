
//=============================================================================
//
// イベントメッセージ処理 [EventMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_MESSAGE_H_
#define _EVENT_MESSAGE_H_

#include "../../Framework/BaseViewer.h"
#include <string>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventMessage :public BaseViewer
{
public:
	EventMessage();
	~EventMessage();

	void Update(void);
	void Draw(void);
	void SetEventMessage(const std::string Message);

	bool isPlaying;

private:
	BaseViewerDrawer *bg;
	TextViewer *text;
};

#endif