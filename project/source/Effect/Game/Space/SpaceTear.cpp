//=====================================
//
//SpaceTear.cpp
//機能:時空断裂パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpaceTear.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	SpaceTearControllerコンストラクタ
	***************************************/
	SpaceTearController::SpaceTearController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 20.0f, 20.0f };
		const D3DXVECTOR2 TextureDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, TextureDiv);

		//テクスチャ読み込み
		const char* TexturePath = "data/TEXTURE/Particle/TearSpark.png";
		LoadTexture(TexturePath);

		//パーティクルコンテナ作成
		const size_t MaxParticle = 2048;
		particleContainer.resize(MaxParticle);
		for (auto&& particle : particleContainer)
		{
			particle = new SpaceTear();
		}

		//エミッタコンテナ作成
		const size_t MaxEmitter = 512;
		emitterContainer.resize(MaxEmitter);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new SpaceTearEmitter();
		}
	}

	/**************************************
	SpaceTear staticメンバ
	***************************************/
	const int SpaceTear::MaxLife = 5;
	const int SpaceTear::MinLife = 3;

	/**************************************
	SpaceTearコンストラクタ
	***************************************/
	SpaceTear::SpaceTear() :
		Particle3D(MinLife, MaxLife),
		angleRotate(Math::RandomRange(-20.0f, 20.0f))
	{
		//テクスチャの通し番号をランダムに決定
		int indexU = Math::RandomRange(0, 2);
		int indexV = Math::RandomRange(0, 2);

		uv.u = indexU * 0.5f;
		uv.v = indexV * 0.5f;
	}

	/**************************************
	SpaceTear初期化処理
	***************************************/
	void SpaceTear::Init()
	{
		cntFrame = 0;
		active = true;

		//回転
		transform->Rotate(angleRotate, Vector3::Forward);

		//移動
		float posY = Math::RandomRange(-1.0f, 1.0f);
		transform->Move(Vector3::Up * posY);

		//スケーリング
		initScaleX = Math::RandomRange(0.5f, 2.0f);
		initScaleY = Math::RandomRange(0.5f, 1.5f);
		transform->SetScale({ initScaleX, initScaleY, 1.0f });
	}

	/**************************************
	SpaceTear更新処理
	***************************************/
	void SpaceTear::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float scaleY = Easing::EaseValue(t, initScaleY, 0.0f, EaseType::InCubic);
		transform->SetScale({ initScaleX, scaleY, 1.0 });
	}

	/**************************************
	SpaceTearEmitterコンストラクタ
	***************************************/
	SpaceTearEmitter::SpaceTearEmitter() :
		BaseEmitter(1, 0)
	{

	}

	/**************************************
	SpaceTearEmitterアクティブ判定
	***************************************/
	bool SpaceTearEmitter::IsActive() const
	{
		if (!active)
			return false;

		return true;

		//シーン終了まで放出させ続けさせたいので
		//カウントでのアクティブ判定は行わない
	}

}