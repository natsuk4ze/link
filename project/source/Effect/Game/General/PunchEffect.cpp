//=====================================
//
//PunchEffect.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PunchEffect.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	PunchEffectControllerコンストラクタ
	**************************************/
	PunchEffectController::PunchEffectController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 0.25f, 0.25f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, TexDiv);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/punchEffect.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new PunchEffect();
		}

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 4;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(15, 0);
		}
	}

	/**************************************
	PunchEffectコンストラクタ
	***************************************/
	PunchEffect::PunchEffect() :
		Particle3D(5, 10)
	{

	}

	/**************************************
	PunchEffect初期化処理
	***************************************/
	void PunchEffect::Init()
	{
		cntFrame = 0;
		active = true;

		initScale = Math::RandomRange(0.8f, 1.2f);

		const float OffsetRange = 1.0f;
		transform->Move(transform->Right() * Math::RandomRange(-OffsetRange, OffsetRange));
		transform->Move(transform->Up() * Math::RandomRange(-OffsetRange, OffsetRange));

		transform->SetRotation(Vector3::Zero);

		uv.u = Math::RandomRange(0, 2) * 0.5f;
		uv.v = Math::RandomRange(0, 2) * 0.5f;
	}

	/**************************************
	PunchEffect更新処理
	***************************************/
	void PunchEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		float scale = Easing::EaseValue(t, initScale, 0.0f, InBack);
		transform->SetScale(scale * Vector3::One);
	}

}
