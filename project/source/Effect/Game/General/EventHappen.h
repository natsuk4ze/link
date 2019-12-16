//=====================================
//
// EventHappen.h
// 機能:イベント発生エフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EVENTHAPPEN_H_
#define _EVENTHAPPEN_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	EventHappenController
	***************************************/
	class EventHappenController : public BaseParticleController
	{
	public:
		EventHappenController();
	};

	/**************************************
	EventHappen
	***************************************/
	class EventHappen : public Particle3D
	{
	public:
		EventHappen();

		void Init();
		void Update();

	private:
		float initScale;
	};
}



#endif