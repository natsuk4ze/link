//=====================================
//
//Blackhole.cpp
//機能:ブラックホールパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Blackhole.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Camera/Camera.h"

namespace Effect::Game
{
	/**************************************
	staticメンバ
	***************************************/
	const float Blackhole::InitOffset = 6.0f;
	const float Blackhole::RangeHeight = 3.0f;

	/**************************************
	BlackholeControllerコンストラクタ
	***************************************/	
	BlackholeController::BlackholeController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 3.0f, 3.0f };
		MakeUnitBuffer(SizeParticle);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/blackhole.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 4096;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new Blackhole();
		}

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 512;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BlackholeEmitter();
		}
	}

	/**************************************
	Blackholeコンストラクタ
	***************************************/
	Blackhole::Blackhole() :
		Particle3D(15),
		position(Vector3::Zero)
	{

	}

	/**************************************
	Blackhole初期化処理
	***************************************/
	void Blackhole::Init()
	{
		cntFrame = 0;
		active = true;

		position = transform->GetPosition();

		initAngle = Math::RandomRange(-D3DX_PI, D3DX_PI);

		height = Math::RandomRange(-RangeHeight, RangeHeight);

		initScale = Math::RandomRange(0.5f, 1.2f);
	}

	/**************************************
	Blackhole更新処理
	***************************************/
	void Blackhole::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;
		float t = (float)cntFrame / lifeFrame;
		float angle = t * D3DX_PI * 0.5f;
		float length = Easing::EaseValue(t, InitOffset, InitOffset * 0.1f, EaseType::InOutCubic);
		
		D3DXVECTOR3 currentPosition = position + D3DXVECTOR3(cosf(angle + initAngle), 0.0f, sinf(angle + initAngle)) * length;
		currentPosition.y = position.y + Easing::EaseValue(t, height, 0.0f, EaseType::InOutCubic);
		transform->SetPosition(currentPosition);

		float scale = Easing::EaseValue(t, initScale, initScale * 0.1f, EaseType::InOutCubic);
		transform->SetScale(Vector3::One * scale);
	}

	/**************************************
	BlackholeEmitterコンストラクタ
	***************************************/
	BlackholeEmitter::BlackholeEmitter() :
		BaseEmitter(5)
	{
	}

	/**************************************
	BlackholeEmitter放出処理
	***************************************/
	bool BlackholeEmitter::Emit(std::vector<BaseParticle*>& container)
	{
		//描画領域外だったら放出しない
		D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());
		if (screenPos.x < 0.0f || screenPos.x >(float)SCREEN_WIDTH || screenPos.y < 0.0f || screenPos.y >(float)SCREEN_HEIGHT)
			return true;

		return BaseEmitter::Emit(container);
	}

	/**************************************
	BlackholeEmitterアクティブ判定
	***************************************/
	bool BlackholeEmitter::IsActive() const
	{
		return active;
	}

}