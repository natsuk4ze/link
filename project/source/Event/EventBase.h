//=============================================================================
//
// イベント基底クラス [EventBase.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _EVENTBASE_H_
#define _EVENTBASE_H_

#include <string>
#include <vector>
#include "../Field/FieldController.h"
#include "../Field/Place/PlaceConfig.h"

using namespace std;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventBase
{
protected:
	bool UseFlag;
	static Field::FieldController *fieldController;

public:
	EventBase();
	~EventBase();
	virtual void Update(void);
	virtual void Draw(void);
	virtual string GetEventMessage(int FieldLevel) = 0;
	bool GetUse(void) { return this->UseFlag; };
	static void ReceiveFieldController(Field::FieldController *Ptr);
};

#endif
