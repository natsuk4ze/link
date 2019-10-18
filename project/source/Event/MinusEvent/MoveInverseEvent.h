//=============================================================================
//
// μ½]CxgNX [MoveInverseEvent.h]
// Author : HAL GP12B332 41 M»
//
//=============================================================================
#ifndef _MoveInverseEvent_H_
#define _MoveInverseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// NXθ`
//*****************************************************************************
class MoveInverseEvent : public EventBase
{
private:
	int RemainTime;

public:
	MoveInverseEvent(int RemainTime);
	~MoveInverseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
