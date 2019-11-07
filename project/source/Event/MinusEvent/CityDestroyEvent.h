//=============================================================================
//
// 町消滅イベントクラス [CityDestroyEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _CityDestroyEvent_H_
#define _CityDestroyEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BeatGame;
class EventViewer;
class EventActorBase;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CityDestroyEvent : public EventBase
{
private:
	D3DXVECTOR3 MeteoritePos;
	D3DXVECTOR3 TownPos;
	D3DXVECTOR3 MoveDirection;
	int EventState;
	const Field::Model::PlaceModel* Target;

	BeatGame *beatGame;
	EventViewer* eventViewer;
	EventActorBase *Meteor;

public:
	CityDestroyEvent(EventViewer* eventViewer);
	~CityDestroyEvent();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void MeteorFallStart(void);
	void CountdownStart(void);
	void EventOver(void);
	void ReceiveBeatResult(bool IsSuccess);
};

#endif
