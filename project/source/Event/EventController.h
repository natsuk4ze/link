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

//*****************************************************************************
// クラス定義
//*****************************************************************************

class EventController
{
private:
	struct EventInfo
	{
		int x;
		int z;
		int EventType;
	};

	std::vector<EventInfo> EventCSVData;
	std::vector<EventBase*> EventVec;
	int FieldLevel;

	void LoadCSV(const char* FilePath);

#if _DEBUG
	void DrawDebug(void);
#endif

public:
	EventController(int FieldLevel);
	~EventController();
	void ReceiveEvent(void);
	void Update(void);
	void Draw(void);
};

#endif
