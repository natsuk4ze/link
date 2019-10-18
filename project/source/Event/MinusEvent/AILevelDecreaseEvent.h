//=============================================================================
//
// AIレベル減少イベントクラス [AILevelDecreaseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _AILevelDecreaseEvent_H_
#define _AILevelDecreaseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class AILevelDecreaseEvent : public EventBase
{
private:
public:
	AILevelDecreaseEvent();
	~AILevelDecreaseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
