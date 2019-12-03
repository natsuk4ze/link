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
class ViewerAnimater;

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

	//メッセージセット処理
	void SetEventMessage(const std::string &message, int &cnt);

	//再生状態取得処理
	bool GetIsPlaying(void);

private:
	BaseViewerDrawer *bg;
	TextViewer *text;
	ViewerAnimater *anim;

	//メッセージセットカウンター
	int messageSetCnt;
};

#endif