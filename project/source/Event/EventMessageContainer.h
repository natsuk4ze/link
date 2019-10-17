//=============================================================================
//
// イベントメッセージコンテナクラス [EventMessageContainer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _EventMessageContainer_H_
#define _EventMessageContainer_H_

#include <vector>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventMessageContainer
{
private:
	//std::vector<const char*> MessageContainer;

public:
	EventMessageContainer();
	~EventMessageContainer();
	static void GetEventMessage(int FieldLevel, int EventType, const char** MessagePtr);
};

#endif
