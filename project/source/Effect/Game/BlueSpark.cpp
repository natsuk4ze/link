//=====================================
//
//青いスパーク処理[BlueSpark.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BlueSpark.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	BlueSparkControllerコンストラクタ
	***************************************/
	BlueSparkController::BlueSparkController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 ParticleSize{ 18.0f, 10.0f };
		MakeUnitBuffer(ParticleSize);

		//テクスチャ読み込み
		const char* path = "data/TEXTURE/Particle/blueSpark.png";
		LoadTexture(path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new BlueSpark();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 4;
		const int NumEmit = 22;
		const int DurationEmit = (int)(30 * 2.0f);

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	BlueSpark staticメンバ
	***************************************/
	const int BlueSpark::MaxLife = 15;
	const int BlueSpark::MinLife = 5;

	/**************************************
	BlueSparkコンストラクタ
	***************************************/
	BlueSpark::BlueSpark() :
		Particle3D(MinLife, MaxLife),
		angleRotate(Math::RandomRange(0.0f, 360.0f))
	{

	}

	/**************************************
	BlueSpark初期化処理
	***************************************/
	void BlueSpark::Init()
	{
		cntFrame = 0;
		active = true;

		//回転
		transform->Rotate(angleRotate, Vector3::Back);

		//移動
		float posY = Math::RandomRange(-5.0f, 5.0f);
		transform->Move(Vector3::Up * posY);

		//スケーリング
		initScaleX = Math::RandomRange(0.1f, 3.0f);
		initScaleY = Math::RandomRange(0.5f, 1.5f);
		transform->SetScale({ initScaleX, initScaleY, 1.0f });
	}

	/**************************************
	BlueSpark更新処理
	***************************************/
	void BlueSpark::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float scaleY = Easing::EaseValue(t, initScaleY, 0.0f, EaseType::InCubic);
		transform->SetScale({ initScaleX, scaleY, 1.0f });
	}
}