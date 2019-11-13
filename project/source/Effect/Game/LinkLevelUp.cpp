//=====================================
//
//LinkLevelUp.cpp
//機能:リンクレベルアップ時の2Dパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "LinkLevelUp.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	コンストラクタ
	***************************************/
	LinkLevelUpController::LinkLevelUpController() :
		BaseParticleController(Particle_2D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 100.0f, -100.0f };
		const D3DXVECTOR2 DivParticle = { 4.0f, 4.0f };
		MakeUnitBuffer(SizeParticle, DivParticle);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/levelup.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new LinkLevelUp();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 32;
		const int DurationEmit = 5;
		const int NumEmit = 30;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	LinkLevelUpコンストラクタ
	***************************************/
	LinkLevelUp::LinkLevelUp() :
		Particle2D(20, 45),
		speed(Math::RandomRange(10.0f, 45.0f)),
		initScale(Math::RandomRange(0.2f, 1.0f)),
		directionMove(Vector3::Random())
	{
		directionMove.z = 0.0f;
		directionMove = Vector3::Normalize(directionMove);
	}

	/**************************************
	LinkLevelUpデストラクタ
	***************************************/
	LinkLevelUp::~LinkLevelUp()
	{
	}

	/**************************************
	LinkLevelUp初期化処理
	***************************************/
	void LinkLevelUp::Init()
	{
		cntFrame = 0;
		active = true;

		int randomIndex = Math::RandomRange(0, 16);
		uv.u = randomIndex % 4 / 4.0f;
		uv.v = randomIndex / 4 / 4.0f;

		transform->Move(directionMove * 30.0f);
	}

	/**************************************
	LinkLevelUp更新処理
	***************************************/
	void LinkLevelUp::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InCubic);
		transform->SetScale(Vector3::One * scale);

		transform->Move(speed * directionMove);
	}
}