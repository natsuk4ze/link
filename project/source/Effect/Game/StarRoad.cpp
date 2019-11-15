//=====================================
//
//StarRoad.cpp
//機能:星の道パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "StarRoad.h"

namespace Effect::Game
{
	/**************************************	
	StarRoadControllerコンストラクタ
	***************************************/
	StarRoadController::StarRoadController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 3.0f, 3.0f };
		MakeUnitBuffer(SizeParticle);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/star.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 1024; 
		particleContainer.resize(MaxParticle);
		for (auto&& particle : particleContainer)
		{
			particle = new StarRoad();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 32;
		emitterContainer.resize(MaxEmitter);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new StarRoadEmitter();
		}
	}

	/**************************************
	StarRoadコンストラクタ
	***************************************/
	StarRoad::StarRoad() :
		Particle3D(15)
	{

	}

	/**************************************
	StarRoad初期化処理
	***************************************/
	void StarRoad::Init()
	{
		const float RangeXZ = 2.0f;
		const float RangeY = 1.0f;

		D3DXVECTOR3 offset = {
			Math::RandomRange(-RangeXZ, RangeXZ),
			Math::RandomRange(-RangeY, RangeY),
			Math::RandomRange(-RangeXZ, RangeXZ)
		};

		transform->Move(offset);

		cntFrame = 0;
		active = true;
	}

	/**************************************
	StarRoad更新処理
	***************************************/
	void StarRoad::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		uv.u += 0.02f;
		uv.v -= 0.02f;
	}

	/**************************************
	StarRoadEmitterコンストラクタ
	***************************************/
	StarRoadEmitter::StarRoadEmitter() :
		BaseEmitter(2)
	{
	}

	/**************************************
	StarRoadEmitterアクティブ判定
	***************************************/
	bool StarRoadEmitter::IsActive() const
	{
		//一度セットされたら無限に放出し続ける
		return active;
	}

}