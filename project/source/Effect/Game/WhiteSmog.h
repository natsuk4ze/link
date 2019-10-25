//=====================================
//
//WhiteSmog.h
//機能:白スモッグ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _WHITESMOG_H_
#define _WHITESMOG_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	WhiteSmogControllerクラス
	***************************************/
	class WhiteSmogController : public BaseParticleController
	{
	public:
		WhiteSmogController();
	};

	/**************************************
	WhiteSmogクラス
	***************************************/
	class WhiteSmog : public AnimationParticle3D
	{
	public:
		WhiteSmog();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;
		static const float MaxSpeed, MinSpeed;
	
		D3DXVECTOR3 directionMove;
		float speedMove;
	};
}
#endif