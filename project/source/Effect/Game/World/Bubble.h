//=============================================================================
//
// 泡エフェクトクラス [Bubble.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _Bubble_H_
#define _Bubble_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"

/**************************************
前方宣言
***************************************/

namespace Effect::Game
{
	/**************************************
	BubbleControllerクラス
	***************************************/
	class BubbleController : public BaseParticleController
	{
	public:
		BubbleController();
	};

	/**************************************
	Bubbleクラス
	***************************************/
	class Bubble : public Particle3D
	{
	public:
		Bubble();

		void Init() override;
		void Update() override;

	private:
		static const int MinLife, MaxLife;
		static const float MinSpeed, MaxSpeed;

		const float Speed;
		const float Scale;
	};
}


#endif