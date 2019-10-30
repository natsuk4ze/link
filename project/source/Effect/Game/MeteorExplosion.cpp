//=============================================================================
//
// 隕石爆発エフェクトクラス [MeteorExplosion.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "MeteorExplosion.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	MeteorExplosionControllerコンストラクタ
	***************************************/
	MeteorExplosionController::MeteorExplosionController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 15.0f, 15.0f };
		const D3DXVECTOR2 DivineTex{ 8.0f, 8.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/MeteorExplosion.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new MeteorExplosion();
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
	MeteorExplosion staticメンバ
	***************************************/
	const int MeteorExplosion::Life = 20;

	/**************************************
	MeteorExplosionコンストラクタ
	***************************************/
	MeteorExplosion::MeteorExplosion() : AnimationParticle3D(8.0f, 8.0f, Life)
	{
	}

	/**************************************
	MeteorExplosion初期化処理
	***************************************/
	void MeteorExplosion::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	MeteorExplosion更新処理
	***************************************/
	void MeteorExplosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//経過時間でアニメーション
		float t = (float)cntFrame / lifeFrame;
		Animation(t);
	}
}