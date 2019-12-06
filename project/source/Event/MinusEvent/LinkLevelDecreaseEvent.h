//=============================================================================
//
// リンクレベル減少イベントクラス [LinkLevelDecreaseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _LinkLevelDecreaseEvent_H_
#define _LinkLevelDecreaseEvent_H_

#include "../EventBase.h"
#include <string>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class LinkLevelDecreaseEvent : public EventBase
{
private:
	static const std::string CityMessage[3];
	static const std::string WorldMessage[3];
	static const std::string SpaceMessage[3];

public:
	LinkLevelDecreaseEvent();
	~LinkLevelDecreaseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
