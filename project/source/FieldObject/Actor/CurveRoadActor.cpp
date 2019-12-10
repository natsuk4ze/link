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
#include "../../Effect/SpaceParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// コンストラクタ
//=====================================
CurveRoadActor::CurveRoadActor()
	: PlaceActor(),
	onWater(false)
{

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
// 初期化処理
//=====================================
void CurveRoadActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel, bool onWater)
{
	PlaceActor::Init(pos, currentLevel);

	this->onWater = onWater;

	using Field::Actor::ActorLoader;
	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::CurveTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterCurve.c_str(), mesh);

	type = Field::Model::Road;

	if (currentLevel == Field::FieldLevel::Space)
	{
		emitterContainer.resize(2, nullptr);
		D3DXVECTOR3 euler = transform->GetEulerAngle();

		for (auto&& emitter : emitterContainer)
		{
			//エミッターセット
			emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::StarRoad, *transform);

			if (emitter != nullptr)
				emitter->SetRotatition(euler);

			euler.y -= 90.0f;
		}
	}
}

//=====================================
// 終了処理
//=====================================
void CurveRoadActor::Uninit()
{
	PlaceActor::Uninit();
	for (auto&& emitter : emitterContainer)
	{
		if (emitter != nullptr)
			emitter->SetActive(false);
	}
	emitterContainer.clear();
}

//=====================================
// 描画処理
//=====================================
void CurveRoadActor::Draw()
{
	//水上なら水位に高さを合わせる
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

//=====================================
// 海上判定設定
//=====================================
void CurveRoadActor::OnSea(bool state)
{
	this->onWater = state;

	using Field::Actor::ActorLoader;
	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::CurveTag[Field::FieldLevel::World].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterCurve.c_str(), mesh);
}
