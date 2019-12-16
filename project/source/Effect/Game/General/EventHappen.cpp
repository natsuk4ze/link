//=====================================
//
//イベント発生エフェクト処理[EventHappen.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EventHappen.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	EventHappenControllerコンストラクタ
	***************************************/
	EventHappenController::EventHappenController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 1.0f, 1.0f };
		const D3DXVECTOR2 DivTex = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, DivTex);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/eventInfo.png");

		//パーティクルコンテナ作成
		const unsigned Maxparticle = 512;
		particleContainer.resize(Maxparticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EventHappen();
		}

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 16;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(15, 20);
		}
	}

	/**************************************
	EventHappenコンストラクタ
	***************************************/
	EventHappen::EventHappen() :
		Particle3D(15, 30)
	{
	}

	/**************************************
	EventHappen初期化処理
	***************************************/
	void EventHappen::Init()
	{
		cntFrame = 0;
		active = true;

		initScale = Math::RandomRange(0.8f, 1.5f);

		D3DXVECTOR3 offset = Vector3::Zero;
		offset.x = Math::RandomRange(-5.0f, 5.0f);
		offset.z = Math::RandomRange(-5.0f, 5.0f);
		transform->Move(offset);
	}

	/**************************************
	EventHappen更新処理
	***************************************/
	void EventHappen::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InCubic);
		transform->SetScale(scale * Vector3::One);

		transform->Move(1.5f * Vector3::Up);
	}
}


