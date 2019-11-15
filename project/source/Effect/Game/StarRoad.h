//=====================================
//
//StarRoad.h
//機能:星の道パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STARROAD_H_
#define _STARROAD_H_

#include "../../../main.h"
#include "../../../Framework/Particle/3D/Particle3D.h"
#include "../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	StarRoadControllerクラス
	***************************************/
	class StarRoadController : public BaseParticleController
	{
	public:
		StarRoadController();
	};

	/**************************************
	StarRoadクラス
	***************************************/
	class StarRoad : public Particle3D
	{
	public:
		StarRoad();

		void Init();
		void Update();

		void Toward(const D3DXVECTOR3& direction);

	private:
		static const float RangeX;
		static const float RangeY;
		static const float RangeZ;

		D3DXVECTOR3 direction;
	};

	/**************************************
	StarRoadEmitterクラス
	***************************************/
	class StarRoadEmitter : public BaseEmitter
	{
	public:
		StarRoadEmitter();

		bool Emit(std::vector<BaseParticle*>& container) override;
		bool IsActive() const override;
	};
}

#endif