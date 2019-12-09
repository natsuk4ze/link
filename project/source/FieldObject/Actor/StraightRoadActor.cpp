//=====================================
//
// ストレートロードアクター[StraightRoadActor.cpp]
// 機能：まっすぐな道用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "StraightRoadActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Effect/SpaceParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// コンストラクタ
//=====================================
StraightRoadActor::StraightRoadActor()
	: PlaceActor(),
	emitter(nullptr),
	onWater(onWater)
{

}

//=====================================
// デストラクタ
//=====================================
StraightRoadActor::~StraightRoadActor()
{
	if (emitter != nullptr)
	{
		emitter->SetActive(false);
		emitter = nullptr;
	}
}

//=====================================
// 初期化処理
//=====================================
void StraightRoadActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel, bool onWataer)
{
	PlaceActor::Init(pos, currentLevel);

	using Field::Actor::ActorLoader;

	this->onWater = onWataer;

	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::StraightTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterStraight.c_str(), mesh);

	if (currentLevel == Field::FieldLevel::Space)
	{
		emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::StarRoad, *transform);
	}
}

//=====================================
// 終了処理
//=====================================
void StraightRoadActor::Uninit()
{
	PlaceActor::Uninit();
	if (emitter != nullptr)
	{
		emitter->SetActive(false);
		emitter = nullptr;
	}
}

//=====================================
// 描画処理
//=====================================
void StraightRoadActor::Draw()
{
	//水上なら高さを水面に合わせる
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
void StraightRoadActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	if (emitter != nullptr)
	{
		D3DXVECTOR3 euler = transform->GetEulerAngle();
		emitter->SetRotatition(euler);
	}
}

//=====================================
// 海上判定設定
//=====================================
void StraightRoadActor::OnSea(bool state)
{
	using Field::Actor::ActorLoader;

	this->onWater = state;

	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::StraightTag[Field::FieldLevel::World].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterStraight.c_str(), mesh);
}
