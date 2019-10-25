//=====================================
//
//青いスパークの破片エフェクト処理[BlueDebris.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BlueDebris.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	BlueDebrisControllerコンストラクタ
	***************************************/
	BlueDebrisController::BlueDebrisController()
	{
		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/blueDebris.png");

		//単位頂点バッファ作成
		const D3DXVECTOR2 ParticleSize{ 1.0f, 1.0f };
		const D3DXVECTOR2 TextureDiv{ (float)BlueDebris::TexDiv, (float)BlueDebris::TexDiv };
		MakeUnitBuffer(ParticleSize, TextureDiv);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new BlueDebris();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 4;
		const int DurationEmit = (int)(30 * 2.0f);
		const int NumEmit = 25;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	BlueDebris statciメンバ
	***************************************/
	const int BlueDebris::MinLife = 10;
	const int BlueDebris::MaxLife = 20;
	const float BlueDebris::MinSpeed = 10.0f;
	const float BlueDebris::MaxSpeed = 3.0f;
	const int BlueDebris::TexDiv = 3;

	/**************************************
	BlueDebrisコンストラクタ
	***************************************/
	BlueDebris::BlueDebris() :
		Particle3D(MinLife, MaxLife),
		InitSpeed(Math::RandomRange(MinSpeed, MaxSpeed)),
		moveDirection(Vector3::Zero)
	{
	}

	/**************************************
	BlueDebris初期化処理
	***************************************/
	void BlueDebris::Init()
	{
		cntFrame = 0;
		active = true;

		//スケーリング
		float scale = Math::RandomRange(0.2f, 1.2f);
		transform->SetScale(Vector3::One * scale);

		//移動方向を設定
		moveDirection = Vector3::Random();

		//UV座標を決定
		int indexUV = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = indexUV % TexDiv / (float)TexDiv;
		uv.v = indexUV / TexDiv / (float)TexDiv;

		//初期位置を移動方向へオフセット
		const float InitOffset = 10.0f;
		transform->Move(moveDirection * InitOffset);
	}

	/**************************************
	BlueDebris更新処理
	***************************************/
	void BlueDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//スピードをイージングで求めて移動計算
		float t = (float)cntFrame / lifeFrame;
		float speed = Easing::EaseValue(t, InitSpeed, 0.5f, EaseType::OutCirc);
		transform->Move(moveDirection * speed);

		//スケール計算
		float scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InCubic);
		transform->SetScale(Vector3::One * scale);

		//回転
		const float angleRotate = 10.0f;
		transform->Rotate(0.0f, 0.0f, angleRotate);
	}

}