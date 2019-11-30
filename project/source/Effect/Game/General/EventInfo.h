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

	private:
		float initScale;
		float speed;
	};

	/**************************************
	EventInfoEmitter
	***************************************/
	class EventInfoEmitter : public BaseEmitter
	{
	public:
		EventInfoEmitter();

		virtual void Init(std::function<void()>& callback) override;
		virtual void Update() override;
		virtual bool Emit(std::vector<BaseParticle*>& container) override;

		const static int PeriodEmit;
	};
}
#endif