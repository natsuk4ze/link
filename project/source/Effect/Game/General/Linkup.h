//=====================================
//
// Linkup.h
// 機能:リンクアップエフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _LINKUP_H_
#define _LINKUP_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	LinkupController
	***************************************/
	class LinkupController : public BaseParticleController
	{
	public:
		LinkupController();
	};

	/**************************************
	Linkup
	***************************************/
	class Linkup : public Particle3D
	{
	public:
		Linkup();

		void Init();
		void Update();

	private:
		float initScale;
	};
}



#endif