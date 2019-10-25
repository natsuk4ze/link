//=============================================================================
//
// 爆発エフェクトクラス [Explosion.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "Explosion.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	ExplosionControllerコンストラクタ
	***************************************/
	ExplosionController::ExplosionController()
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 30.0f, 30.0f };
		const D3DXVECTOR2 DivineTex{ 4.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/MeteorExplosion.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new Explosion();
		}

		//エミッターコンテナ作成処理
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;
		const int DurationEmit = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit);
		}
	}

	/**************************************
	Explosion staticメンバ
	***************************************/
	const int Explosion::Life = 20;
	const float Explosion::Speed = 3.0f;

	/**************************************
	Explosionコンストラクタ
	***************************************/
	Explosion::Explosion() :
		AnimationParticle(4.0f, 2.0f, Life),
		speedMove(Speed)
	{
	}

	/**************************************
	Explosion初期化処理
	***************************************/
	void Explosion::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	Explosion更新処理
	***************************************/
	void Explosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//経過時間でアニメーション
		float t = (float)cntFrame / lifeFrame;
		Animation(t);

		//イージングで移動
		//float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::Linear);
		//transform->Move(speed * directionMove);
	}
}