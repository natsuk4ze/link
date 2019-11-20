//=====================================
//
//AngryFace.h
//機能:怒り顔2Dパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ANGRYFACE_H_
#define _ANGRYFACE_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/2D/Particle2D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	AngryFaceControllerクラス
	***************************************/
	class AngryFaceController : public BaseParticleController
	{
	public:
		AngryFaceController();
	};

	/**************************************
	AngryFaceクラス
	***************************************/
	class AngryFace : public Particle2D
	{
	public:
		AngryFace();
		~AngryFace();

		void Init();
		void Update();

	private:
		static const int Life;

		float targetScale;
	};
}
#endif