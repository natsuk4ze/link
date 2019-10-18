//=============================================================================
//
// 操作反転イベントクラス [MoveInverseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _MoveInverseEvent_H_
#define _MoveInverseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class MoveInverseEvent : public EventBase
{
private:
public:
	MoveInverseEvent();
	~MoveInverseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
