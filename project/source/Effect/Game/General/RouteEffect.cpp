//=====================================
//
//RouteEffect.cpp
//機能:ルートエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RouteEffect.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	staticメンバ
	***************************************/
	const float RouteEffect::InitSpeed = 0.3f;

	/**************************************
	RouteEffectControllerコンストラクタ	
	***************************************/
	RouteEffectController::RouteEffectController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 2.0f, 2.0f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, TexDiv);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/EventInfo.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new RouteEffect();
		}

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(10, 0);
		}
	}

	/**************************************
	RouteEffectControllerコンストラクタ
	***************************************/
	RouteEffect::RouteEffect() :
		Particle3D(30, 60)
	{

	}

	/**************************************
	RouteEffectControllerコンストラクタ
	***************************************/
	void RouteEffect::Init()
	{
		cntFrame = 0;
		active = true;

		moveDir = Vector3::Random();
	}

	/**************************************
	RouteEffectControllerコンストラクタ
	***************************************/
	void RouteEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(moveDir * InitSpeed);

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);
	}

}

