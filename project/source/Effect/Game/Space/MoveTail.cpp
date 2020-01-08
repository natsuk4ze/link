//=============================================================================
//
// 移動の軌跡エフェクトクラス [MoveTail.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "MoveTail.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	MoveTailControllerコンストラクタ
	***************************************/
	MoveTailController::MoveTailController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 ParticleSize{ 15.0f, 15.0f };
		MakeUnitBuffer(ParticleSize);

		//テクスチャ読み込み
		const char* path = "data/TEXTURE/Particle/MoveTail.png";
		LoadTexture(path);

		//エミッターコンテナ作成
		const unsigned MaxParticle = 64;
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;
		const int DurationEmit = 40;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
			emitter->CreateParticleContainer<MoveTail>(MaxParticle);
		}
	}

	/**************************************
	描画
	***************************************/
	bool MoveTailController::Draw(void)
	{
		bool Result = false;
		LPDIRECT3DDEVICE9 Device = GetDevice();

		//レンダーステートを加算合成に設定
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		Result = BaseParticleController::Draw();

		//レンダーステートを元に戻す
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		return Result;
	}

	/**************************************
	Emitterの位置を設定
	***************************************/
	void MoveTailController::SetEmitterPos(D3DXVECTOR3 Pos)
	{
		for (auto&& emitter : emitterContainer)
		{
			if (emitter->IsActive())
				emitter->SetPosition(Pos);
		}
	}

	/**************************************
	MoveTail staticメンバ
	***************************************/
	const int MoveTail::Life = 15;

	/**************************************
	MoveTailコンストラクタ
	***************************************/
	MoveTail::MoveTail() :
		Particle3D(Life)
	{
	}

	/**************************************
	MoveTail初期化処理
	***************************************/
	void MoveTail::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	MoveTail更新処理
	***************************************/
	void MoveTail::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float Time = (float)cntFrame / (float)Life;

		float Scale = Easing::EaseValue(Time, 1.0f, 0.0f, EaseType::InCubic);
		transform->SetScale(Vector3::One * Scale);
	}
}