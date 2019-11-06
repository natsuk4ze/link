//=============================================================================
//
// 移動の残像エフェクトクラス [Tail.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "Tail.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	TailControllerコンストラクタ
	***************************************/
	TailController::TailController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 ParticleSize{ 1.0f, 1.0f };
		MakeUnitBuffer(ParticleSize);

		//テクスチャ読み込み
		const char* path = "data/TEXTURE/Particle/Tail.png";
		LoadTexture(path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new Tail();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;
		const int DurationEmit = 90;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	Tail staticメンバ
	***************************************/
	const int Tail::Life = 10;

	/**************************************
	Tailコンストラクタ
	***************************************/
	Tail::Tail() :
		Particle3D(Life)
	{
	}

	/**************************************
	Tail初期化処理
	***************************************/
	void Tail::Init()
	{
		cntFrame = 0;
		active = true;

		//初期位置を移動方向へオフセット
		//float BaseAngle = 10.0f;
		//float Theta = Math::RandomRange(0, 36) * BaseAngle;
		//float Length = Math::RandomRange(0.0f, 15.0f);
		//D3DXVECTOR3 InitOffset = D3DXVECTOR3
		//(
		//	Length * cosf(D3DXToRadian(Theta)),
		//	Math::RandomRange(0.0f, 1.0f),
		//	Length * sinf(D3DXToRadian(Theta))
		//);
		//transform->Move(InitOffset);

	}

	/**************************************
	Tail更新処理
	***************************************/
	void Tail::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(Vector3::Right * 2.0f);
	}
}