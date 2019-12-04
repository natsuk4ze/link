//=============================================================================
//
// 制限時間回復イベントクラス [TimeRecoveryEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _TimeRecoveryEvent_H_
#define _TimeRecoveryEvent_H_

#include "../EventBase.h"
#include <string>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class TimeRecoveryEvent : public EventBase
{
private:
	static const std::string message[3];

public:
	TimeRecoveryEvent();
	~TimeRecoveryEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
