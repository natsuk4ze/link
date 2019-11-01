//=============================================================================
//
// AIレベル減少イベントクラス [AILevelDecreaseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _AILevelDecreaseEvent_H_
#define _AILevelDecreaseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BeatGame;
class EventViewer;
class EventActor;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class AILevelDecreaseEvent : public EventBase
{
private:
	D3DXVECTOR3 UFOPos;
	D3DXVECTOR3 TownPos;
	int EventState;
	const Field::Model::PlaceModel* Target;

	BeatGame *beatGame;
	EventViewer* eventViewer;
	EventActor *UFO;

public:
	AILevelDecreaseEvent(EventViewer* eventViewer);
	~AILevelDecreaseEvent();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void UFODebutStart(void);
	void ReceiveBeatResult(bool IsSuccess);
	void CountdownStart(void);
	void EventOver(void);
};

#endif
