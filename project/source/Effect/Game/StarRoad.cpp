//=====================================
//
//StarRoad.cpp
//機能:星の道パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "StarRoad.h"
#include "../../../Framework/Camera/Camera.h"

namespace Effect::Game
{
	/**************************************
	StarRoad staticメンバ
	***************************************/
	const float StarRoad::RangeX = 2.0f;
	const float StarRoad::RangeY = 1.0f;
	const float StarRoad::MaxRangeZ = 8.0f;
	const float StarRoad::MinRangeZ = -2.0f;

	/**************************************	
	StarRoadControllerコンストラクタ
	***************************************/
	StarRoadController::StarRoadController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 6.0f, 6.0f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, TexDiv);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/star.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 2048; 
		particleContainer.resize(MaxParticle);
		for (auto&& particle : particleContainer)
		{
			particle = new StarRoad();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 1024;
		emitterContainer.resize(MaxEmitter);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new StarRoadEmitter();
		}
	}

	/**************************************
	StarRoadコンストラクタ
	***************************************/
	StarRoad::StarRoad() :
		Particle3D(15),
		direction(transform->Forward())
	{

	}

	/**************************************
	StarRoad初期化処理
	***************************************/
	void StarRoad::Init()
	{
		D3DXVECTOR3 offset = Vector3::Zero;
		offset += transform->Right() * Math::RandomRange(-RangeX, RangeX);
		offset += transform->Up() * Math::RandomRange(-RangeY, RangeY);
		offset += transform->Forward() * Math::RandomRange(MinRangeZ, MaxRangeZ);

		transform->Move(offset);

		transform->SetRotation(Vector3::Zero);

		uv.u = Math::RandomRange(0, 2) * 0.5f;
		uv.v = Math::RandomRange(0, 2) * 0.5f;


		cntFrame = 0;
		active = true;
	}

	/**************************************
	StarRoad更新処理
	***************************************/
	void StarRoad::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(direction * 0.2f);
	}

	/**************************************
	StarRoad移動方向設定処理
	***************************************/
	void StarRoad::Toward(const D3DXVECTOR3 & direction)
	{
		this->direction = direction;
	}

	/**************************************
	StarRoadEmitterコンストラクタ
	***************************************/
	StarRoadEmitter::StarRoadEmitter() :
		BaseEmitter(3)
	{
	}

	/**************************************
	StarRoadEmitter放出処理
	***************************************/
	bool StarRoadEmitter::Emit(std::vector<BaseParticle*>& container)
	{
		if (!IsActive())
			return true;

		//描画領域外だったら放出しない
		D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());
		if (screenPos.x < 0.0f || screenPos.x >(float)SCREEN_WIDTH * 1.2f || screenPos.y < 0.0f || screenPos.y >(float)SCREEN_HEIGHT * 1.2f)
			return true;

		UINT cntEmit = 0;
		for (auto& particle : container)
		{
			if (particle->IsActive())
				continue;

			//初期化処理
			particle->SetTransform(*transform);
			dynamic_cast<StarRoad*>(particle)->Toward(transform->Forward());
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
	StarRoadEmitterアクティブ判定
	***************************************/
	bool StarRoadEmitter::IsActive() const
	{
		//一度セットされたら無限に放出し続ける
		return active;
	}

}