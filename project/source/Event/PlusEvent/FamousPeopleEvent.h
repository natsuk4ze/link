//=============================================================================
//
// 有名人イベントクラス [FamousPeopleEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _FamousPeopleEvent_H_
#define _FamousPeopleEvent_H_

#include "../EventBase.h"
#include <string>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FamousPeopleEvent : public EventBase
{
private:
	int RemainTime;
	static const std::string message[3];

public:
	FamousPeopleEvent();
	~FamousPeopleEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
