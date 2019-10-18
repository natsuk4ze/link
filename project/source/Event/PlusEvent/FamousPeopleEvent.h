//=============================================================================
//
// 有名人イベントクラス [FamousPeopleEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _FamousPeopleEvent_H_
#define _FamousPeopleEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FamousPeopleEvent : public EventBase
{
private:
public:
	FamousPeopleEvent();
	~FamousPeopleEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
