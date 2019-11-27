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
#include "../../../../Framework/Particle/BaseEmitter.h"

class EventViewer;
class PlanetActor;
class EventCamera;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NewTownEvent_Space : public EventBase
{
private:
	EventViewer *eventViewer;
	PlanetActor *PlanetModel;
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 BuildPos;
	const Field::Model::PlaceModel* NewPlanet;
	int EventState;
	int CountFrame;
	std::function<void(void)> EventOverFunc;
	EventCamera *camera;
	BaseEmitter* MoveTailEmitter;
	BaseEmitter* StarDustEmitter;

public:
	NewTownEvent_Space(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera* camera);
	~NewTownEvent_Space();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void FallenStart(void);
	//void EventOver(void);
};

#endif
