//=============================================================================
//
// ストック回数回復イベントクラス [StockRecoveryEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _StockRecoveryEvent_H_
#define _StockRecoveryEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class StockRecoveryEvent : public EventBase
{
private:
public:
	StockRecoveryEvent();
	~StockRecoveryEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
