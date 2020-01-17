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

#include <map>

//*****************************************************************************
// 前方宣言(おーはま追記)
//*****************************************************************************
class EventViewer;
class BoardPolygon;
class EventViewerParam;
class EventCamera;
class BeatGameViewer;
class BaseEmitter;

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
	//bool IsViewerPlaying;

	std::map<Field::FieldPosition, BaseEmitter*> infoEmitterContainer;

	void LoadCSV(const char* FilePath);

#if _DEBUG
	BoardPolygon *polygon;
	void DrawDebug(void);
#endif

public:
	EventController(int FieldLevel, int csvNo);
	~EventController();

	void Init(int FieldLevel, int csvNo);
	void Init_Tutorial(void);
	void Uninit(void);
	void Update(void);
	void UpdateViewer(void);
	void DrawEventObject(void);
	void DrawEventViewer(void);
	bool CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& route, int FieldLevel);
	void ReceiveFieldEventHandler(FieldEventHandler *Ptr);
	void SetBanStock(bool Flag);
	void SetInPause(bool Flag);
	bool GetInPause(void);
	bool EventDebug(int fieldLevel);
	void ClearEventViewer(void);
	bool IsEmptyEventVec() const;

	friend class PresenDebugController;
};

#endif
