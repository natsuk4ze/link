//=====================================
//
//GaugeDebris.h
//機能:ゲージの破片パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAUDEDEBRIS_H_
#define _GAUDEDEBRIS_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/2D/Particle2D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	GaudeParticleController
	***************************************/
	class GaugeDebrisController : public BaseParticleController
	{
	public :
		GaugeDebrisController();

	};

	/**************************************
	GaugeDebris
	***************************************/
	class GaugeDebris : public Particle2D
	{
	public:
		GaugeDebris();

		void Init();
		void Update();

	private:
		D3DXVECTOR3 moveDir;
		float speed;
		float initScale;
	};
}


#endif