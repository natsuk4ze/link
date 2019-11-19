//=====================================
//
//WhirlPoolBubble.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "WhirlPoolBubble.h"
#include "../../../../Framework/Camera/Camera.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	staticメンバ
	***************************************/
	const float WhirlPoolBubble::LengthPopup = 1.0f;
	const float WhirlPoolBubble::LengthOffset = 5.0f;

	/**************************************
	WhirlPoolControllerコンストラクタ
	***************************************/
	WhirlPoolController::WhirlPoolController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 1.5f, 1.5f };
		MakeUnitBuffer(SizeParticle);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/WhirlPoolBubble.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 4096;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new WhirlPoolBubble();
		}

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 512;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new WhirlPoolBubbleEmitter();
		}
	}

	/**************************************
	WhirlPoolBubbleコンストラクタ
	***************************************/
	WhirlPoolBubble::WhirlPoolBubble() :
		Particle3D(20),
		position(Vector3::Zero)
	{

	}

	/**************************************
	WhirlPoolBubble初期化処理
	***************************************/
	void WhirlPoolBubble::Init()
	{
		cntFrame = 0;
		active = true;

		position = transform->GetPosition();

		initOffset = Math::RandomRange(-D3DX_PI, D3DX_PI);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);
	}

	/**************************************
	WhirlPoolBubble更新処理
	***************************************/
	void WhirlPoolBubble::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;
		float t = (float)cntFrame / lifeFrame * D3DX_PI * 0.2f;
		float popup = sinf(t * 10.0f) * LengthPopup;

		D3DXVECTOR3 currentPosition = position + D3DXVECTOR3(cosf(t + initOffset) * LengthOffset, popup, sinf(t + initOffset) * LengthOffset);
		transform->SetPosition(currentPosition);
	}

	/**************************************
	WhirlPoolBubbleEmiterコンストラクタ
	***************************************/
	WhirlPoolBubbleEmitter::WhirlPoolBubbleEmitter() :
		BaseEmitter(3)
	{
	}

	/**************************************
	WhirlPoolBubbleEmitter放出処理
	***************************************/
	bool WhirlPoolBubbleEmitter::Emit(std::vector<BaseParticle*>& container)
	{
		if (!IsActive())
			return true;

		//描画領域外だったら放出しない
		D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());
		if (screenPos.x < 0.0f || screenPos.x >(float)SCREEN_WIDTH || screenPos.y < 0.0f || screenPos.y >(float)SCREEN_HEIGHT)
			return true;

		UINT cntEmit = 0;
		for (auto& particle : container)
		{
			if (particle->IsActive())
				continue;

			//初期化処理
			particle->SetTransform(*transform);
			particle->Init();

			//カウント
			cntEmit++;

			//決められ数だけ放出していたら終了
			if (cntEmit == emitNum)
				return true;
		}

		return false;
	}

	/**************************************
	WhirlPoolBubbleEmitterアクティブ判定
	***************************************/
	bool WhirlPoolBubbleEmitter::IsActive() const
	{
		//一度セットされたら無限に放出し続ける
		return active;
	}

}