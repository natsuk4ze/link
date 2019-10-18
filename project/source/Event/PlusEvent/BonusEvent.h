//=============================================================================
//
// 町発展度ボーナスイベントクラス [BonusEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BonusEvent_H_
#define _BonusEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BonusEvent : public EventBase
{
private:
public:
	BonusEvent();
	~BonusEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
