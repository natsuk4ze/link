//=====================================
//
//カラフルデブリパーティクル処理[ColorfulDebris.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ColorfulDebris.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	ColorfulDebrisControllerコンストラクタ
	***************************************/
	ColorfulDebrisController::ColorfulDebrisController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{0.6f, 0.6f};
		const D3DXVECTOR2 TextureDivine{ (float)ColorfulDebris::TexDiv, (float)ColorfulDebris::TexDiv };
		MakeUnitBuffer(SizeParticle, TextureDivine);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/colorfulDebris.png";
		LoadTexture(Path);

		//エミッタコンテナ作成
		const unsigned MaxParticle = 64;
		const unsigned MaxEmitter = 32;
		const int DurationEmit = 3;
		const int NumEmit = 50;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
			emitter->CreateParticleContainer<ColorfulDebris>(MaxParticle);
		}
	}

	/**************************************
	ColorfulDebris staticメンバ
	***************************************/
	const int ColorfulDebris::MinLife = 15;
	const int ColorfulDebris::MaxLife = 30;
	const float ColorfulDebris::MinSpeed = 0.5f;
	const float ColorfulDebris::MaxSpeed = 3.5f;
	const float ColorfulDebris::MinScale = 0.5;
	const float ColorfulDebris::MaxScale = 1.3f;
	const int ColorfulDebris::TexDiv = 6;

	/**************************************
	ColorfulDebrisコンストラクタ
	***************************************/
	ColorfulDebris::ColorfulDebris() :
		Particle3D(MinLife, MaxLife),
		initSpeed(Math::RandomRange(MinSpeed, MaxSpeed)),
		initScale(Math::RandomRange(MinScale, MaxScale)),
		directionMove(Vector3::Random())
	{
		directionMove.y = Math::RandomRange(0.0f, 0.5f);
		D3DXVec3Normalize(&directionMove, &directionMove);
	}

	/**************************************
	ColorfulDebris初期化処理
	***************************************/
	void ColorfulDebris::Init()
	{
		int randomIndex = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = randomIndex % TexDiv * 1.0f / TexDiv;
		uv.v = randomIndex / TexDiv * 1.0f / TexDiv;

		cntFrame = 0;
		active = true;

		//ランダムにZ軸回転
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//移動方向に初期座標をオフセット
		transform->Move(directionMove * 2.5f);

	}

	/**************************************
	ColorfulDebris更新処理
	***************************************/
	void ColorfulDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		const float EndSpeed = 0.05f;
		float speed = Easing::EaseValue(t, initSpeed, EndSpeed, EaseType::OutCubic);
		transform->Move(speed * directionMove);

		const float EndScale = 0.0f;
		float scale = Easing::EaseValue(t, initScale, EndScale, EaseType::InQuint);
		transform->SetScale(Vector3::One * scale);

		const float angleRotate = 33.0f;
		transform->Rotate(0.0f, 0.0f, angleRotate);
	}

}