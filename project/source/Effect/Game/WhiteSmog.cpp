//=====================================
//
//WhiteSmog.cpp
//機能:白スモッグ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "WhiteSmog.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	WhiteSmogControllerコンストラクタ
	***************************************/
	WhiteSmogController::WhiteSmogController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 5.0f, 5.0f };
		const D3DXVECTOR2 DivineTex{ 8.0f, 8.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/smog.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new WhiteSmog();
		}

		//エミッターコンテナ作成処理
		const unsigned MaxEmitter = 64;
		const int NumEmit = 10;
		const int DurationEmit = 5;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	WhiteSmog staticメンバ
	***************************************/
	const int WhiteSmog::MaxLife = 60;
	const int WhiteSmog::MinLife = 40;
	const float WhiteSmog::MaxSpeed = 1.0f;
	const float WhiteSmog::MinSpeed = 0.25f;

	/**************************************
	WhiteSmogコンストラクタ
	***************************************/
	WhiteSmog::WhiteSmog() :
		AnimationParticle3D(8.0f, 8.0f, MinLife, MaxLife),
		directionMove(Vector3::Random()),
		speedMove(Math::RandomRange(MinSpeed, MaxSpeed))
	{
		directionMove.y = fabsf(directionMove.y);
		D3DXVec3Normalize(&directionMove, &directionMove);
	}

	/**************************************
	WhiteSmog初期化処理
	***************************************/
	void WhiteSmog::Init()
	{
		cntFrame = 0;
		active = true;

		//ランダムにZ軸回転
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//移動方向に初期座標をオフセット
		float offset = Math::RandomRange(0.5f, 2.5f);
		transform->Move(directionMove * offset);

		//スケールをランダムに変更
		float scale = Math::RandomRange(0.2f, 1.1f);
		transform->SetScale(scale * Vector3::One);
	}

	/**************************************
	WhiteSmog更新処理
	***************************************/
	void WhiteSmog::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//経過時間でアニメーション
		float t = (float)cntFrame / lifeFrame;
		Animation(t);

		//イージングで移動
		float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::OutCubic);
		transform->Move(speed * directionMove);
	}
}