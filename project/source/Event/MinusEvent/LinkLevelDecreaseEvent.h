//=============================================================================
//
// リンクレベル減少イベントクラス [LinkLevelDecreaseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _LinkLevelDecreaseEvent_H_
#define _LinkLevelDecreaseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class LinkLevelDecreaseEvent : public EventBase
{
private:
public:
	LinkLevelDecreaseEvent();
	~LinkLevelDecreaseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
