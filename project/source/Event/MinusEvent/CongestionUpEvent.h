//=============================================================================
//
// 混雑度上昇イベントクラス [CongestionUpEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _CongestionUpEvent_H_
#define _CongestionUpEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CongestionUpEvent : public EventBase
{
private:
public:
	CongestionUpEvent();
	~CongestionUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
