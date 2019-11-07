//=====================================
//
// Planetアクター[PlanetActor.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _PlanetActor_H_
#define _PlanetActor_H_

#include "EventActorBase.h"
#include "../../../Framework/Particle/BaseEmitter.h"

//**************************************
// クラス定義
//**************************************
class PlanetActor : public EventActorBase
{
private:
	BaseEmitter* MoveTailEmitter;

#if _DEBUG
	D3DXVECTOR3 Pos;
	int FrameCount;
	void HoverMotion(void);
#endif

public:
	PlanetActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~PlanetActor();

	void Update() override;
};

#endif
