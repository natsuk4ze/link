//=============================================================================
//
// 町レベル上昇イベントクラス [CityLevelUpEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _CityLevelUpEvent_H_
#define _CityLevelUpEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CityLevelUpEvent : public EventBase
{
private:
public:
	CityLevelUpEvent();
	~CityLevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
