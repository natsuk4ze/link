//=============================================================================
//
// 町消滅エフェクトクラス [TownExplosion.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "TownExplosion.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	TownExplosionControllerコンストラクタ
	***************************************/
	TownExplosionController::TownExplosionController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 30.0f, 30.0f };
		const D3DXVECTOR2 DivineTex{ 4.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/TownExplosion.png";
		LoadTexture(Path);

		//エミッターコンテナ作成処理
		const unsigned MaxParticle = 1;
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;
		const int DurationEmit = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit);
			emitter->CreateParticleContainer<TownExplosion>(MaxParticle);
		}
	}

	/**************************************
	TownExplosion staticメンバ
	***************************************/
	const int TownExplosion::Life = 20;

	/**************************************
	TownExplosionコンストラクタ
	***************************************/
	TownExplosion::TownExplosion() : AnimationParticle3D(4.0f, 2.0f, Life)
	{

	}

	/**************************************
	TownExplosion初期化処理
	***************************************/
	void TownExplosion::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	TownExplosion更新処理
	***************************************/
	void TownExplosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//経過時間でアニメーション
		float t = (float)cntFrame / lifeFrame;
		Animation(t);
	}
}