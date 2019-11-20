//=============================================================================
//
// AIレベル減少エフェクトクラス [Darkness.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "Darkness.h"
#include "../../../../Framework/Math/Easing.h"

// 一回放出するパーティクルの数
static const int OnceParticleNum = 4;

namespace Effect::Game
{
	/**************************************
	DarknessControllerコンストラクタ
	***************************************/
	DarknessController::DarknessController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 2.0f, 2.0f };
		const D3DXVECTOR2 DivineTex{ 2.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/DarknessDebris.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new Darkness();
		}

		//エミッターコンテナ作成処理
		const unsigned MaxEmitter = 1;
		const int NumEmit = 8;
		const int DurationEmit = 90;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	Darkness staticメンバ
	***************************************/
	const int Darkness::MinLife = 30;
	const int Darkness::MaxLife = 50;
	const float Darkness::MinSpeed = 0.7f;
	const float Darkness::MaxSpeed = 0.3f;
	const int Darkness::TexDiv = 2;

	/**************************************
	Darknessコンストラクタ
	***************************************/
	Darkness::Darkness() :
		Particle3D(MinLife, MaxLife),
		Speed(Math::RandomRange(MinSpeed, MaxSpeed))
	{
	}

	/**************************************
	Darkness初期化処理
	***************************************/
	void Darkness::Init()
	{
		static int ParticleCount = 0;

		cntFrame = 0;
		active = true;
		ParticleCount++;
		ParticleCount %= 36;

		//UV座標を決定
		int indexUV = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = indexUV % TexDiv / (float)TexDiv;
		uv.v = indexUV / TexDiv / (float)TexDiv;

		//初期位置を移動方向へオフセット
		float BaseAngle = 360.0f / 36;
		//float Theta = Math::RandomRange(0, 36) * BaseAngle;
		float Theta = ParticleCount * BaseAngle;
		D3DXVECTOR3 InitOffset = D3DXVECTOR3
		(
			7.0f * cosf(D3DXToRadian(Theta)),
			Math::RandomRange(15.0f, 20.0f),
			//20.0f,
			7.0f * sinf(D3DXToRadian(Theta))
		);
		transform->Move(InitOffset);
	}

	/**************************************
	Darkness更新処理
	***************************************/
	void Darkness::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(Vector3::Down * Speed);
		if (transform->GetPosition().y <= 0.0f)
		{
			SetActive(false);
		}
	}
}