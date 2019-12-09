//=====================================
//
// クロスジャンクションアクター[CrossJunctionActor.cpp]
// 機能：十字路3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CrossJunctionActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Effect/SpaceParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// コンストラクタ
//=====================================
CrossJunctionActor::CrossJunctionActor()
	: PlaceActor(),
	onWater(false)
{
	type = Field::Model::Junction;
}

//=====================================
// デストラクタ（メッシュの開放は基底クラスで）
//=====================================
CrossJunctionActor::~CrossJunctionActor()
{
	for (auto&& emitter : emitterContainer)
	{
		if (emitter == nullptr)
			continue;

		emitter->SetActive(false);
	}
}

//=====================================
// 初期化処理
//=====================================
void CrossJunctionActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel, bool onWater)
{
	PlaceActor::Init(pos, currentLevel);

	this->onWater = onWater;

	using Field::Actor::ActorLoader;
	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::CrossTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterCross.c_str(), mesh);

	if (currentLevel == Field::FieldLevel::Space)
	{
		D3DXVECTOR3 euler = transform->GetEulerAngle();
		emitterContainer.resize(4, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::StarRoad, *transform);
			if (emitter != nullptr)
			{
				emitter->SetRotatition(euler);
			}

			euler.y += 90.0f;
		}
	}
}

//=====================================
// 終了処理
//=====================================
void CrossJunctionActor::Uninit()
{
	PlaceActor::Uninit();
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
void CrossJunctionActor::Draw()
{
	//水面なら高さを合わせる
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
void CrossJunctionActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	D3DXVECTOR3 euler = transform->GetEulerAngle();
	for (auto&& emitter : emitterContainer)
	{
		if (emitter == nullptr)
			continue;

		emitter->SetRotatition(euler);
		euler.y += 90.0f;
	}
}

//=====================================
// 海上判定設定
//=====================================
void CrossJunctionActor::OnSea(bool state)
{
	using Field::Actor::ActorLoader;

	onWater = state;

	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::CrossTag[Field::FieldLevel::World].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterCross.c_str(), mesh);
}
