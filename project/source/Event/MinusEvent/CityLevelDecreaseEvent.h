//=============================================================================
//
// 町レベル減少イベントクラス [CityLevelDecreaseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _CityLevelDecreaseEvent_H_
#define _CityLevelDecreaseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CityLevelDecreaseEvent : public EventBase
{
private:
public:
	CityLevelDecreaseEvent();
	~CityLevelDecreaseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
