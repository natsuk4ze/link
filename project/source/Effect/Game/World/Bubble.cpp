//=============================================================================
//
// 泡エフェクトクラス [Bubble.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "Bubble.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	BubbleControllerコンストラクタ
	***************************************/
	BubbleController::BubbleController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 ParticleSize{ 1.0f, 1.0f};
		MakeUnitBuffer(ParticleSize);

		//テクスチャ読み込み
		const char* path = "data/TEXTURE/Particle/Bubble.png";
		LoadTexture(path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new Bubble();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 1;
		const int NumEmit = 64;
		const int DurationEmit = 90;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	Bubble staticメンバ
	***************************************/
	const int Bubble::MaxLife = 15;
	const int Bubble::MinLife = 5;
	const float Bubble::MinSpeed = 0.4f;
	const float Bubble::MaxSpeed = 0.1f;

	/**************************************
	Bubbleコンストラクタ
	***************************************/
	Bubble::Bubble() :
		Particle3D(MinLife, MaxLife),
		Speed(Math::RandomRange(MinSpeed, MaxSpeed)),
		Scale(Math::RandomRange(0.1f, 1.0f))
	{

	}

	/**************************************
	Bubble初期化処理
	***************************************/
	void Bubble::Init()
	{
		cntFrame = 0;
		active = true;

		//初期位置を移動方向へオフセット
		float BaseAngle = 10.0f;
		float Theta = Math::RandomRange(0, 36) * BaseAngle;
		float Length = Math::RandomRange(0.0f, 15.0f);
		D3DXVECTOR3 InitOffset = D3DXVECTOR3
		(
			Length * cosf(D3DXToRadian(Theta)),
			Math::RandomRange(0.0f, 1.0f),
			Length * sinf(D3DXToRadian(Theta))
		);
		transform->Move(InitOffset);

		//スケーリング
		transform->SetScale({ Scale, Scale, 1.0f });
	}

	/**************************************
	Bubble更新処理
	***************************************/
	void Bubble::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(Vector3::Up * Speed);
	}
}