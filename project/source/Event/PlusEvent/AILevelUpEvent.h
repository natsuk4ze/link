//=============================================================================
//
// AIレベル上昇イベントクラス [AILevelUpEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _AILevelUpEvent_H_
#define _AILevelUpEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class AILevelUpEvent : public EventBase
{
private:
public:
	AILevelUpEvent();
	~AILevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
