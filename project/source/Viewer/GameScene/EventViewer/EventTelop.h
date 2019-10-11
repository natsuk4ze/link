
//=============================================================================
//
// イベントテロップ処理 [EventTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_TELOP_H_
#define _EVENT_TELOP_H_

#include "../EventViewer/EventViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;
//template<class T> class DelegateBase;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventTelop :public EventViewer
{
public:
	EventTelop();
	~EventTelop();

	enum TelopID
	{

	};


	void Update(void);
	void Draw(void);
	//void Set(TelopID id, DelegateBase onFinish);

private:
	BaseViewerDrawer *bg;
	BaseViewerDrawer *text;
	//DelegateBase* onFinish;
};

#endif