//=====================================
//
//GaugeDebris.cpp
//機能:ゲージの破片パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GaugeDebris.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	GaugeDebrisControllerコンストラクタ
	***************************************/
	GaugeDebrisController::GaugeDebrisController() :
		BaseParticleController(Particle_2D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 80.0f, -80.0f };
		const D3DXVECTOR2 TexDiv = {2.0f, 2.0f};
		MakeUnitBuffer(Size, TexDiv);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/gaugeDebris.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new GaugeDebris();
		}

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 16;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(60, 3);
		}
	}

	/**************************************
	GaudeDebrisコンストラクタ
	***************************************/
	GaugeDebris::GaugeDebris() :
		Particle2D(15, 30)
	{
	}

	/**************************************
	GaugeDebris初期化処理
	***************************************/
	void GaugeDebris::Init()
	{
		active = true;
		cntFrame = 0;

		speed = Math::RandomRange(20.0f, 50.0f);

		moveDir = Vector3::Random();
		moveDir.z = 0.0f;
		moveDir.x = fabsf(moveDir.x);

		initScale = Math::RandomRange(0.5f, 1.8f);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

		uv.u = Math::RandomRange(0, 2) * 0.5f;
		uv.v = Math::RandomRange(0, 2) * 0.5f;

		D3DXVECTOR3 offset = Vector3::Zero;
		offset.x += Math::RandomRange(-60.0f, 0.0f);
		offset.y += Math::RandomRange(-60.0f, 60.0f);
		transform->Move(offset);
	}

	/**************************************
	GaugeDebrisControllerコンストラクタ
	***************************************/
	void GaugeDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::OutExpo);
		transform->SetScale(scale * Vector3::One);

		float currentSpeed = Easing::EaseValue(t, speed, 0.0f, EaseType::OutCubic);
		transform->Move(moveDir * currentSpeed);
	}

}

