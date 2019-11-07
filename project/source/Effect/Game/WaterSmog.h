//=============================================================================
//
// 水の霧エフェクトクラス [WaterSmog.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _WaterSmog_H_
#define _WaterSmog_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	WaterSmogControllerクラス
	***************************************/
	class WaterSmogController : public BaseParticleController
	{
	public:
		WaterSmogController();
		void Update(void) override;
		static int FrameCount;
	};

	/**************************************
	WaterSmogクラス
	***************************************/
	class WaterSmog : public AnimationParticle3D
	{
	public:
		WaterSmog();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;
	};
}
#endif