//=============================================================================
//
// 隕石周りの炎エフェクトクラス [MeteorFire.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "MeteorFire.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	MeteorFireControllerコンストラクタ
	***************************************/
	MeteorFireController::MeteorFireController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 10.0f,10.0f};
		const D3DXVECTOR2 DivineTex{ 3.0f, 1.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/MeteorFire2.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new MeteorFire();
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
	MeteorFire staticメンバ
	***************************************/
	const int MeteorFire::Life = 300;

	/**************************************
	MeteorFireコンストラクタ
	***************************************/
	MeteorFire::MeteorFire() : AnimationParticle3D(3.0f, 1.0f, Life)
	{
	}

	/**************************************
	MeteorFire初期化処理
	***************************************/
	void MeteorFire::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	MeteorFire更新処理
	***************************************/
	void MeteorFire::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//経過時間でアニメーション
		AnimIndex++;
		Animation(AnimIndex / 3);
	}
}