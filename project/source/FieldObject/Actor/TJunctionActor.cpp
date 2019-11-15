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
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"

//=====================================
// コンストラクタ
//=====================================
TJunctionActor::TJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::TJunctionTag[currentLevel].c_str(), mesh);

	type = Field::Model::Junction;

	emitterContainer.resize(2, nullptr);

	D3DXVECTOR3 euler = transform->GetEulerAngle();
	euler.y += 90.0f;

	//直線側のエミッターをセット
	BaseEmitter* emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);
	if (emitter != nullptr)
	{
		emitter->SetRotatition(euler);
		emitterContainer[0] = emitter;
	}

	//横道側のエミッターをセット
	euler.y += 90.0f;
	emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);
	if (emitter != nullptr)
	{
		emitter->SetRotatition(euler);
		emitterContainer[1] = emitter;
	}
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
