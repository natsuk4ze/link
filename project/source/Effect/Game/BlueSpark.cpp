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
	BlueSparkController::BlueSparkController()
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 ParticleSize{ 3.0f, 3.0f };
		MakeUnitBuffer(ParticleSize);

		//テクスチャ読み込み
		const char* path = "data/TEXTURE/Particle/blueSpark.png";
		LoadTexture(path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new BlueSpark();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 4;
		const int NumEmit = 5;
		const int DurationEmit = 30 * 4;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	BlueSpark staticメンバ
	***************************************/
	const int BlueSpark::MaxLife = 45;
	const int BlueSpark::MinLife = 20;

	/**************************************
	BlueSparkコンストラクタ
	***************************************/
	BlueSpark::BlueSpark() :
		BaseParticle(MinLife, MaxLife),
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
		float radian = D3DXToRadian(angleRotate);
		transform->Move({cosf(radian), sinf(radian), 0.0f});

		//スケーリング
		transform->SetScale({ 3.0f, 1.0f, 1.0f });
	}

	/**************************************
	BlueSpark更新処理
	***************************************/
	void BlueSpark::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;
	}
}