//=====================================
//
// BlueSpark.h
// 機能:青いスパークエフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLUESPARK_H_
#define _BLUESPARK_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

/**************************************
前方宣言
***************************************/

namespace Effect::Game
{
	/**************************************
	BlueSparkControllerクラス
	***************************************/
	class BlueSparkController : public BaseParticleController
	{
	public:
		BlueSparkController();
	};

	/**************************************
	BlueSparkクラス
	***************************************/
	class BlueSpark : public Particle3D
	{
	public:
		BlueSpark();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;

		float angleRotate;
		float initScaleX;
		float initScaleY;
	};
}


#endif