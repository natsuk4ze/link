//=============================================================================
//
// ストック回数回復イベントクラス [StockRecoveryEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _StockRecoveryEvent_H_
#define _StockRecoveryEvent_H_

#include "../EventBase.h"
#include <string>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class StockRecoveryEvent : public EventBase
{
private:
	static const std::string CityMessage[3];
	static const std::string WorldMessage[3];
	static const std::string SpaceMessage[3];

public:
	StockRecoveryEvent();
	~StockRecoveryEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
