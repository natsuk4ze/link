//=============================================================================
//
// 新しい町イベントクラス [NewTownEventCtrl.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _NewTownEventCtrl_H_
#define _NewTownEventCtrl_H_

#include "../../EventBase.h"
#include "../../../Field/Place/FieldPlaceModel.h"

class EventViewer;
class EventCamera;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NewTownEventCtrl : public EventBase
{
private:
	EventBase *NewTownEvent;
	EventViewer *eventViewer;
	EventCamera *eventCamera;

public:
	NewTownEventCtrl(EventViewer *Ptr, int FieldLevel, EventCamera *camera);
	~NewTownEventCtrl();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	//void CreateNewTown(void);
	virtual void EventOver(void);
};

#endif
