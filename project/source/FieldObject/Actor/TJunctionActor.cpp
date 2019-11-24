//=====================================
//
// Tジャンクションアクター[TJunctionActor.h]
// 機能：T字路3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "TJunctionActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Effect/SpaceParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// コンストラクタ
//=====================================
TJunctionActor::TJunctionActor()
	: PlaceActor(),
	onWater(false)
{
	type = Field::Model::Junction;

	emitterContainer.resize(3, nullptr);
}

//=====================================
// デストラクタ
//=====================================
TJunctionActor::~TJunctionActor()
{
	for (auto&& emitter : emitterContainer)
	{
		if (emitter == nullptr)
			continue;

		emitter->SetActive(false);
	}
	emitterContainer.clear();
}

//=====================================
// 初期化処理
//=====================================
void TJunctionActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel, bool onWater)
{
	PlaceActor::Init(pos, currentLevel);

	using Field::Actor::ActorLoader;
	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::TJunctionTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterT.c_str(), mesh);

	this->onWater = onWater;

	emitterContainer.resize(3, nullptr);

	D3DXVECTOR3 euler = transform->GetEulerAngle();

	if (currentLevel == Field::FieldLevel::Space)
	{
		for (auto&& emitter : emitterContainer)
		{
			euler.y += 90.0f;

			emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::StarRoad, *transform);
			if (emitter != nullptr)
				emitter->SetRotatition(euler);
		}
	}
}

//=====================================
// 終了処理
//=====================================
void TJunctionActor::Uninit()
{
	for (auto&& emitter : emitterContainer)
	{
		if (emitter == nullptr)
			continue;

		emitter->SetActive(false);
	}
	emitterContainer.clear();
}

//=====================================
// 描画処理
//=====================================
void TJunctionActor::Draw()
{
	//水上なら高さを合わせる
	if (onWater)
	{
		D3DXVECTOR3 position = transform->GetPosition();
		position.y = WaterHeightController::GetHeight();
		transform->SetPosition(position);
	}

	PlaceActor::Draw();
}

//=====================================
// 回転処理
//=====================================
void TJunctionActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	D3DXVECTOR3 euler = transform->GetEulerAngle();
	for (auto&& emitter : emitterContainer)
	{
		euler.y += 90.0f;

		if (emitter == nullptr)
			continue;

		emitter->SetRotatition(euler);
	}
}
