//=============================================================================
//
// 町全体リンクレベル上昇イベントクラス [AllLinkLevelUpEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _AllLinkLevelUpEvent_H_
#define _AllLinkLevelUpEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class AllLinkLevelUpEvent : public EventBase
{
private:
public:
	AllLinkLevelUpEvent();
	~AllLinkLevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
