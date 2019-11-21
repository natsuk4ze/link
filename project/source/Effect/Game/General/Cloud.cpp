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
		BaseParticleController(Particle_2D)
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
			emitter = new BaseEmitter(10, 120);
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
		D3DXVECTOR3 position = Vector3::Zero;
		position.x = 2000.0f;
		position.y = Math::RandomRange(0.0f, (float)SCREEN_HEIGHT);
		transform->SetPosition(position);

		velocity = Vector3::Left * Math::RandomRange(20.0f, 75.0f);

		float u = Math::RandomRange(0, 3) / 3.0f;
		float v = Math::RandomRange(0, 2) / 2.0f;
		uv = ParticleUV(u, v);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

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
	}
}

