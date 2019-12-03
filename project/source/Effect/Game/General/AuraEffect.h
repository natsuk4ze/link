//=====================================
//
//AuraEffect.h
//機能:オーラエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _AURAEFFECT_H_
#define _AURAEFFECT_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseEmitter.h"

namespace Effect::Game
{
	/**************************************
	AuraEffectController
	***************************************/
	class AuraEffectController : public BaseParticleController
	{
	public:
		AuraEffectController();

		BaseEmitter* SetEmitter(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, std::function<void()> callback);
	};

	/**************************************
	AuraEffect
	***************************************/
	class AuraEffect : public Particle3D
	{
	public:
		AuraEffect();

		void Init() override;
		void Update() override;

	private:
		D3DXVECTOR3 moveDir;
		float initScale;
	};
}


#endif