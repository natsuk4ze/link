//=============================================================================
//
// イベントコントローラークラス [EventController.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _EVENTCONTROLLER_H_
#define _EVENTCONTROLLER_H_

#include "EventBase.h"
#include <vector>
#include "../Field/FieldController.h"
#include "../Viewer/GameScene/EventViewer/EventViewer.h"


//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventController
{
	struct EventInfo
	{
		int x;
		int z;
		int EventType;
	};

private:
	std::vector<EventInfo> EventCSVData;
	std::vector<EventBase*> EventVec;
	EventViewer *eventViewer;
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
};

#endif
