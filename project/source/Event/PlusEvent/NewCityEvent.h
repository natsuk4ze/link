//=============================================================================
//
// 新しい町イベントクラス [NewCityEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _NewCityEvent_H_
#define _NewCityEvent_H_

#include "../EventBase.h"
#include "../../Field/Place/FieldPlaceModel.h"

class EventViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NewCityEvent : public EventBase
{
private:
	EventViewer *eventViewer;
	const Field::Model::PlaceModel* NewTown;

public:
	NewCityEvent(EventViewer *Ptr);
	~NewCityEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void CreateNewCity(void);
	void EventOver(void);
};

#endif
