//=====================================
//
//Cloud.cpp
//機能:雲パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Cloud.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	staticメンバ
	***************************************/
	const float Cloud::MinSpeed = 10.0f;
	const float Cloud::MaxSpeed = 40.0f;
	const float Cloud::MinPositionX = -100.0f;
	const float Cloud::MaxPositionX = SCREEN_WIDTH + 100.0f;
	const float Cloud::MinPositionY = -100.0f;
	const float Cloud::MaxPositionY = SCREEN_HEIGHT + 100.0f;

	/**************************************
	コンストラクタ
	***************************************/
	CloudController::CloudController() :
		BaseParticleController(Particle_2D, false)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 200.0f, -200.0f };
		const D3DXVECTOR2 DivParticle = { 3.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivParticle);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/cloud.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 1024;
		particleContainer.resize(MaxParticle);
		for (auto&& particle : particleContainer)
		{
			particle = new Cloud();
		}

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 4;
		emitterContainer.resize(MaxEmitter);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new CloudEmitter();
		}
	}

	/**************************************
	Cloudコンストラクタ
	***************************************/
	Cloud::Cloud() :
		Particle2D(60)
	{

	}

	/**************************************
	Cloud初期化処理
	***************************************/
	void Cloud::Init()
	{
		float u = Math::RandomRange(0, 3) / 3.0f;
		float v = Math::RandomRange(0, 2) / 2.0f;
		uv = ParticleUV(u, v);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

		initScale = Math::RandomRange(0.8f, 2.0f);
		transform->SetScale(Vector3::One * initScale);

		cntFrame = 0;
		active = true;
	}

	/**************************************
	Cloud更新処理
	***************************************/
	void Cloud::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(velocity);

		transform->Rotate(0.5f, Vector3::Forward);

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);
	}

	/**************************************
	Cloud方向設定処理
	***************************************/
	void Cloud::SetDirection(bool isDown)
	{
		if (isDown)
		{
			D3DXVECTOR3 position = Vector3::Zero;
			position.x = Math::RandomRange(MinPositionX, MaxPositionX);
			position.y = MinPositionY;
			transform->SetPosition(position);

			velocity = Vector3::Normalize({ -1.0f, 1.0f, 0.0f }) * Math::RandomRange(MinSpeed, MaxSpeed);
		}
		else
		{
			D3DXVECTOR3 position = Vector3::Zero;
			position.x = Math::RandomRange(MinPositionX, MaxPositionX);
			position.y = MaxPositionY;
			transform->SetPosition(position);

			velocity = Vector3::Normalize({ 1.0f, -1.0f, 0.0f }) * Math::RandomRange(MinSpeed, MaxSpeed);
		}
	}

	/**************************************
	CloudEmitterコンストラクタ
	***************************************/
	CloudEmitter::CloudEmitter() :
		BaseEmitter(14, 30)
	{

	}

	/**************************************
	CloudEmitter放出処理
	***************************************/
	bool CloudEmitter::Emit(std::vector<BaseParticle*>& container)
	{
		if (!IsActive())
			return true;

		int cntEmit = 0;
		for (auto&& particle : container)
		{
			if (particle->IsActive())
				continue;

			//初期化処理
			Cloud* entity = dynamic_cast<Cloud*>(particle);
			entity->SetDirection(cntEmit < emitNum / 2);
			entity->Init();

			cntEmit++;

			if (cntEmit == emitNum)
				return true;
		}

		return false;
	}
}

