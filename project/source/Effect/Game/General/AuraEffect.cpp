//=====================================
//
//AuraEffect.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AuraEffect.h"
#include "../../../../Framework/Math/Easing.h"
#include <algorithm>

namespace Effect::Game
{
	/**************************************
	AuraEffectControllerコンストラクタ
	***************************************/
	AuraEffectController::AuraEffectController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 2.0f, 2.0f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, TexDiv);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/auraParticle.png");

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 1;
		const unsigned MaxParticle = 256;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(15, 0);
			emitter->CreateParticleContainer<AuraEffect>(MaxParticle);
		}
	}

	/**************************************
	AuraEffectControllerエミッタセット処理
	***************************************/
	BaseEmitter * AuraEffectController::SetEmitter(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & direction, std::function<void()> callback)
	{
		auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
		{
			return !emitter->IsActive();
		});

		if (emitter == emitterContainer.end())
			return NULL;

		BaseEmitter* ptr = (*emitter);

		Transform transform = Transform(pos, Vector3::Zero, Vector3::One);
		transform.LookAt(pos + direction);
		ptr->SetTransform(transform);
		ptr->Init(callback);

		return ptr;
	}

	/**************************************
	AuraEffectコンストラクタ
	***************************************/
	AuraEffect::AuraEffect() :
		Particle3D(10, 30)
	{

	}

	/**************************************
	AuraEffect初期化処理
	***************************************/
	void AuraEffect::Init()
	{
		active = true;
		cntFrame = 0;
		initScale = Math::RandomRange(0.8f, 1.2f);
		
		transform->Move(Vector3::Random());
		
		moveDir = transform->Forward();

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

		uv.u = Math::RandomRange(0, 2) * 0.5f;
		uv.v = Math::RandomRange(0, 2) * 0.5f;
	}

	/**************************************
	AuraEffect更新処理
	***************************************/
	void AuraEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(moveDir * 0.2f);

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::OutExpo);

		transform->SetScale(Vector3::One * scale);
	}
}
