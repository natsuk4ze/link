//=====================================
//
//EventInfo.cpp
//機能:イベントインフォパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EventInfo.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	staticメンバ
	***************************************/
	const int EventInfoEmitter::PeriodEmit = 90;

	/**************************************
	EventInfoEffectControllerコンストラクタ
	***************************************/
	EventInfoEffectController::EventInfoEffectController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 0.5f, 0.5f };
		const D3DXVECTOR2 Div = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, Div);

		//テクスチャ読み込み
		const char* TexName = "data/TEXTURE/Particle/eventInfo.png";
		LoadTexture(TexName);
		
		//エミッタコンテナ作成
		//イベントマスの最大数
		const unsigned MaxParticle = 64;
		const unsigned MaxEmitter = 128;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EventInfoEmitter();
			emitter->CreateParticleContainer<EventInfoEffect>(MaxParticle);
		}
	}

	/**************************************
	EventInfoEffectコンストラクタ
	***************************************/
	EventInfoEffect::EventInfoEffect() :
		Particle3D(20, 40)
	{

	}

	/**************************************
	EventInfoEffect初期化処理
	***************************************/
	void EventInfoEffect::Init()
	{
		active = true;
		cntFrame = 0;

		initScale = Math::RandomRange(0.8f, 1.5f);

		float offset = Math::RandomRange(-4.0f, 4.0f);
		transform->Move(Vector3::Right * offset);

		offset = Math::RandomRange(-4.0f, 4.0f);
		transform->Move(Vector3::Forward * offset);

		uv.u = 0.5f * Math::RandomRange(0, 2);
		uv.v = 0.5f * Math::RandomRange(0, 2);

		speed = Math::RandomRange(0.05f, 0.3f);
	}

	/**************************************
	EventInfoEffect更新処理
	***************************************/
	void EventInfoEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(scale * Vector3::One);

		transform->Move(Vector3::Up * speed);
	}

	/**************************************
	EventInfoEffectEmitterコンストラクタ
	***************************************/
	EventInfoEmitter::EventInfoEmitter() :
		BaseEmitter(60, 0)
	{
		UseCulling(true);
	}

	/**************************************
	EventInfoEffectEmitter初期化処理
	***************************************/
	void EventInfoEmitter::Init(const std::function<void()>& callback)
	{
		cntFrame = Math::RandomRange(0, PeriodEmit);
		active = true;
		isFinished = false;
		enableEmit = true;

		for (auto&& particle : particleContainer)
		{
			particle->SetActive(false);
		}
	}

	/**************************************
	EventInfoEffectEmitter更新処理
	***************************************/
	void EventInfoEmitter::Update()
	{
		if (!active)
			return;

		cntFrame = Math::WrapAround(0, PeriodEmit, ++cntFrame);

		Emit();

		isFinished = true;
		for (auto&& particle : particleContainer)
		{
			if (!particle->IsActive())
				continue;

			isFinished = false;

			particle->Update();
		}

		if (cntFrame == duration && isFinished && callback != nullptr)
		{
			callback();
		}
	}

	/**************************************
	EventInfoEffectEmitter放出処理
	***************************************/
	bool EventInfoEmitter::Emit()
	{
		if (cntFrame != 0)
			return true;

		return BaseEmitter::Emit();
	}
}
