//=====================================
//
//AngryFace.cpp
//機能:怒り顔2Dパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AngryFace.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	コンストラクタ
	***************************************/
	AngryFaceController::AngryFaceController() :
		BaseParticleController(Particle_2D)
	{
		//単位頂点バッファ作成
		//スクリーン座標で扱うのでYサイズをマイナスにすることに注意
		const D3DXVECTOR2 SizeParticle{ 100.0f, -100.0f };
		MakeUnitBuffer(SizeParticle);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/angryFace.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const int MaxParticle = 1024;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new AngryFace();
		}

		//エミッタコンテナ作成
		const int MaxEmitter = 4;
		const int DurationEmit = 60;
		const int NumEmit = 15;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	AngryFaceコンストラクタ
	***************************************/
	const int AngryFace::Life = 45;

	/**************************************
	AngryFaceコンストラクタ
	***************************************/
	AngryFace::AngryFace() :
		Particle2D(Life),
		targetScale(1.0f)
	{

	}

	/**************************************
	AngryFaceデストラクタ
	***************************************/
	AngryFace::~AngryFace()
	{
	}

	/**************************************
	AngryFace初期化処理
	***************************************/
	void AngryFace::Init()
	{
		targetScale = Math::RandomRange(0.8f, 2.0f);
		cntFrame = 0;
		active = true;

		D3DXVECTOR3 position{
			(float)Math::RandomRange(0, SCREEN_WIDTH),
			(float)Math::RandomRange(0, SCREEN_HEIGHT),
			0.0f
		};
		transform->SetPosition(position);
	}

	/**************************************
	AngryFace更新処理
	***************************************/
	void AngryFace::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame * 2.0f;

		float scale = Easing::EaseValue(t, 0.0f, targetScale, EaseType::InExpo);
		transform->SetScale(scale * Vector3::One);
	}
}