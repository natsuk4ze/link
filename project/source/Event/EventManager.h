//=============================================================================
//
// イベントマネージャークラス [EventManager.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _EventManager_H_
#define _EventManager_H_

#include "EventBase.h"
#include <vector>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventManager
{
private:
	std::vector<EventBase*> EventVec;

public:
	EventManager();
	~EventManager();
	void Update(void);
	void Draw(void);
};

#endif
