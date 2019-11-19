//=============================================================================
//
// 水の霧エフェクトクラス [WaterSmog.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "WaterSmog.h"
#include "../../../../Framework/Math/Easing.h"



namespace Effect::Game
{
	/**************************************
	WaterSmogController staticメンバ
	***************************************/
	int WaterSmogController::FrameCount = 0;

	/**************************************
	WaterSmogControllerコンストラクタ
	***************************************/
	WaterSmogController::WaterSmogController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 5.0f, 5.0f };
		const D3DXVECTOR2 DivineTex{ 8.0f, 8.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/WaterSmog.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new WaterSmog();
		}

		//エミッターコンテナ作成処理
		const unsigned MaxEmitter = 1;
		const int NumEmit = 8;
		const int DurationEmit = 60;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	WaterSmogController更新処理
	***************************************/
	void WaterSmogController::Update(void)
	{
		if (emitterContainer.at(0)->IsActive())
		{
			FrameCount++;
			FrameCount %= 60;
		}
		else
		{
			FrameCount = 0;
		}

		BaseParticleController::Update();
	}

	/**************************************
	WaterSmog staticメンバ
	***************************************/
	const int WaterSmog::MaxLife = 30;
	const int WaterSmog::MinLife = 10;

	/**************************************
	WaterSmogコンストラクタ
	***************************************/
	WaterSmog::WaterSmog() :
		AnimationParticle3D(8.0f, 8.0f, MinLife, MaxLife)
	{
	}

	/**************************************
	WaterSmog初期化処理
	***************************************/
	void WaterSmog::Init()
	{
		cntFrame = 0;
		active = true;

		//ランダムにZ軸回転
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//初期位置を移動方向へオフセット
		float BaseAngle = 10.0f;
		float Theta = Math::RandomRange(0, 36) * BaseAngle;
		float T = (float)WaterSmogController::FrameCount / 60.0f;
		float Length_Max = Easing::EaseValue(T, 5.0f, 15.0f, EaseType::Linear);
		float Length = Math::RandomRange(0.0f, Length_Max);
		D3DXVECTOR3 InitOffset = D3DXVECTOR3
		(
			Length * cosf(D3DXToRadian(Theta)),
			Math::RandomRange(1.0f, 1.5f),
			Length * sinf(D3DXToRadian(Theta))
		);
		transform->Move(InitOffset);

		//スケールをランダムに変更
		float scale = Math::RandomRange(0.5f, 1.0f);
		transform->SetScale(scale * Vector3::One);
	}

	/**************************************
	WaterSmog更新処理
	***************************************/
	void WaterSmog::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//経過時間でアニメーション
		float t = (float)cntFrame / lifeFrame;
		Animation(t);

		//イージングで移動
		//float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::OutCubic);
		//transform->Move(speed * directionMove);
	}
}