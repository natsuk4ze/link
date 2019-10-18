//=============================================================================
//
// イベントコントローラークラス [EventController.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _EVENTCONTROLLER_H_
#define _EVENTCONTROLLER_H_

#include "EventBase.h"
#include "../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../Field/Place/FieldPlaceModel.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventController
{
	struct EventInfo
	{
		Field::FieldPosition Pos;
		int EventType;
	};

private:
	std::vector<EventInfo> EventCSVData;
	std::vector<EventBase*> EventVec;
	EventViewer *eventViewer;
	Field::FieldController *fieldController;
	int FieldLevel;

	void LoadCSV(const char* FilePath);

#if _DEBUG
	void DrawDebug(void);
#endif

public:
	EventController(int FieldLevel);
	~EventController();
	void Update(void);
	void Draw(void);
	void CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& route, int FieldLevel);
	void ReceiveFieldController(Field::FieldController *Ptr);
};

#endif
