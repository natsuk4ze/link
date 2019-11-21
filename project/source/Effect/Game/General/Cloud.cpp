//=====================================
//
//Cloud.cpp
//機能:雲パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Cloud.h"

namespace Effect::Game
{
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
		Particle2D(180)
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

		transform->SetScale(Vector3::One * Math::RandomRange(0.8f, 2.0f));

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
	}

	/**************************************
	Cloud方向設定処理
	***************************************/
	void Cloud::SetDirection(bool isDown)
	{
		if (isDown)
		{
			D3DXVECTOR3 position = Vector3::Zero;
			position.x = Math::RandomRange(-100.0f, 3000.0f);
			position.y = -100.0f;
			transform->SetPosition(position);

			velocity = Vector3::Normalize({ -1.0f, 1.0f, 0.0f }) * Math::RandomRange(20.0f, 75.0f);
		}
		else
		{
			D3DXVECTOR3 position = Vector3::Zero;
			position.x = Math::RandomRange(-100.0f, 3000.0f);
			position.y = SCREEN_HEIGHT + 100.0f;
			transform->SetPosition(position);

			velocity = Vector3::Normalize({ 1.0f, -1.0f, 0.0f }) * Math::RandomRange(20.0f, 75.0f);
		}
	}

	/**************************************
	CloudEmitterコンストラクタ
	***************************************/
	CloudEmitter::CloudEmitter() :
		BaseEmitter(20, 120)
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

