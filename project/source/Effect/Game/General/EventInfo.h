//=====================================
//
//EventInfo.h
//機能:イベントインフォパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EVENTINFO_H_
#define _EVENTINFO_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	EventInfoEffectController
	***************************************/
	class EventInfoEffectController : public BaseParticleController
	{
	public:
		EventInfoEffectController();
	};

	/**************************************
	EventInfoEffect
	***************************************/
	class EventInfoEffect : public Particle3D
	{
	public:
		EventInfoEffect();

		void Init();
		void Update();
	};
}
#endif