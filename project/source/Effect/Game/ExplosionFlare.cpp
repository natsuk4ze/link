//=============================================================================
//
// 火の粉クラス [ExplosionFlare.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "ExplosionFlare.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	ExplosionFlareControllerコンストラクタ
	***************************************/
	ExplosionFlareController::ExplosionFlareController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 1.0f, 1.0f };
		const D3DXVECTOR2 DivineTex{ 2.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/ExplosionFlare.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 128;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new ExplosionFlare();
		}

		//エミッターコンテナ作成処理
		const unsigned MaxEmitter = 3;
		const int NumEmit = 24;
		const int DurationEmit = 3;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	ExplosionFlare staticメンバ
	***************************************/
	const int ExplosionFlare::MaxLife = 30;
	const int ExplosionFlare::MinLife = 20;
	const float ExplosionFlare::MaxSpeed = 2.5f;
	const float ExplosionFlare::MinSpeed = 1.5f;

	/**************************************
	ExplosionFlareコンストラクタ
	***************************************/
	ExplosionFlare::ExplosionFlare() :
		AnimationParticle3D(2.0f, 2.0f, MinLife, MaxLife),
		directionMove(Vector3::Random()),
		speedMove(Math::RandomRange(MinSpeed, MaxSpeed))
	{
		directionMove.y = 0.0f;
		D3DXVec3Normalize(&directionMove, &directionMove);
	}

	/**************************************
	ExplosionFlare初期化処理
	***************************************/
	void ExplosionFlare::Init()
	{
		cntFrame = 0;
		active = true;

		//ランダムにZ軸回転
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//移動方向に初期座標をオフセット
		transform->Move(directionMove * 2.5f);
	}

	/**************************************
	ExplosionFlare更新処理
	***************************************/
	void ExplosionFlare::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//経過時間でアニメーション
		float t = (float)cntFrame / lifeFrame;
		Animation(t);

		//イージングで移動
		float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::InOutExpo);
		transform->Move(speed * directionMove);
	}
}