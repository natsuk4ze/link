//=============================================================================
//
// イベントコントローラークラス [EventController.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _EVENTCONTROLLER_H_
#define _EVENTCONTROLLER_H_

#include "EventBase.h"
#include "../Viewer/GameScene/ParameterContainer/EventViewerParam.h"
#include "../Field/FieldConfig.h"
#include "../Field/FieldEventHandler.h"

//*****************************************************************************
// 前方宣言(おーはま追記)
//*****************************************************************************
class EventViewer;
class BoardPolygon;
class EventViewerParam;
class EventCamera;
class BeatGameViewer;

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
	EventCamera *camera;
	BeatGameViewer *beatViewer;

	bool InBanStock;
	bool InPauseEvent;

	void LoadCSV(const char* FilePath);

#if _DEBUG
	BoardPolygon *polygon;
	void DrawDebug(void);
#endif

public:
	EventController(int FieldLevel);
	~EventController();

	void Init(int FieldLevel);
	void Uninit(void);
	void Update(void);
	void UpdateViewer(void);
	void DrawEventObject(void);
	void DrawEventViewer(void);
	bool CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& route, int FieldLevel);
	void ReceiveFieldEventHandler(FieldEventHandler *Ptr);
	void EmbedViewerParam(EventViewerParam& param);
	void SetBanStock(bool Flag);
	void SetInPause(bool Flag);
	bool GetInPause(void);
};

#endif
