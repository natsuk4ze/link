//=====================================
//
// カーブロードアクター[CurveRoadActor.cpp]
// 機能：カーブ用道3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CurveRoadActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"

//=====================================
// コンストラクタ
//=====================================
CurveRoadActor::CurveRoadActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::CurveTag[currentLevel].c_str(), mesh);

	type = Field::Model::Road;

	if (currentLevel == Field::FieldLevel::Space)
	{
		emitterContainer.resize(2, nullptr);
		D3DXVECTOR3 euler = transform->GetEulerAngle();

		for (auto&& emitter : emitterContainer)
		{
			//エミッターセット
			emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);

			if (emitter != nullptr)
				emitter->SetRotatition(euler);

			euler.y -= 90.0f;
		}
	}

}

//=====================================
// デストラクタ
//=====================================
CurveRoadActor::~CurveRoadActor()
{
	for (auto&& emitter : emitterContainer)
	{
		if (emitter != nullptr)
			emitter->SetActive(false);
	}
}

//=====================================
// 回転処理
//=====================================
void CurveRoadActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	D3DXVECTOR3 euler = transform->GetEulerAngle();
	for (auto&& emitter : emitterContainer)
	{
		if (emitter != nullptr)
		{
			emitter->SetRotatition(euler);
			euler.y -= 90.0f;
		}
	}
}
