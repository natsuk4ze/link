//=============================================================================
//
// 新しい町(宇宙レベル)イベントクラス [NewTownEvent_Space.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _NewTownEvent_Space_H_
#define _NewTownEvent_Space_H_

#include "../../EventBase.h"
#include "../../../Field/Place/FieldPlaceModel.h"

class EventViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NewTownEvent_Space : public EventBase
{
private:
	EventViewer *eventViewer;
	const Field::Model::PlaceModel* NewTown;
	std::function<void(void)> EventOverFunc;

public:
	NewTownEvent_Space(EventViewer *Ptr, std::function<void(void)> EventOverFunc);
	~NewTownEvent_Space();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void CreateNewTown(void);
	//void EventOver(void);
};

#endif
