//=====================================
//
// マウンテンアクター[MountainActor.cpp]
// 機能：山（渦潮、ブラックホール）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "MountainActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Shader/WhirlPoolEffect.h"
#include "../../Field/Object/WaterHeightController.h"
#include "../../Effect/WorldParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Effect/SpaceParticleManager.h"

//=====================================
// コンストラクタ
//=====================================
MountainActor::MountainActor()
	: PlaceActor(),
	effect(nullptr),
	speedWhirl(0.0f),
	emitter(nullptr),
	level(Field::FieldLevel::City),
	onWater(false)
{
	effect = new Field::Actor::WhirlPoolEffect();

	type = Field::Model::Mountain;
}

//=====================================
// デストラクタ
//=====================================
MountainActor::~MountainActor()
{
	SAFE_DELETE(effect);

	if (emitter != nullptr)
	{
		emitter->SetActive(false);
		emitter = nullptr;
	}
}

//=====================================
// 初期化処理
//=====================================
void MountainActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel, bool onWater)
{
	PlaceActor::Init(pos, currentLevel);

	this->level = currentLevel;
	this->onWater = onWater;

	using Field::Actor::ActorLoader;

	if (!onWater)
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::MountainTag[currentLevel].c_str(), mesh);

		if (currentLevel == Field::FieldLevel::Space)
		{
			emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::Blackhole, transform->GetPosition());
			speedWhirl = Math::RandomRange(0.005f, 0.01f);
		}
	}
	else
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::WhirlPoolTag.c_str(), mesh);

		emitter = WorldParticleManager::Instance()->Generate(WorldParticle::WhirlPoolBubble, transform->GetPosition());
		speedWhirl = Math::RandomRange(0.02f, 0.05f);
	}
}

//=====================================
// 終了処理
//=====================================
void MountainActor::Uninit()
{
	if (emitter != nullptr)
	{
		emitter->SetActive(false);
		emitter = nullptr;
	}
}

//=====================================
// 更新処理
//=====================================
void MountainActor::Update()
{
	//水上 or 宇宙の場合は回転させる
	if (onWater || level == Field::FieldLevel::Space)
	{
		cntWhirl += speedWhirl;
		effect->SetTime(cntWhirl);
	}

	//水上なら渦潮エミッタを水面にあわせる
	if (onWater)
	{
		D3DXVECTOR3 position = emitter->GetPosition();
		position.y = WaterHeightController::GetHeight();
		emitter->SetPosition(position);
	}

	PlaceActor::Update();
}

//=====================================
// 描画処理
//=====================================
void MountainActor::Draw()
{
	if (onWater)
	{
		//高さを水面に合わせる
		D3DXVECTOR3 position = transform->GetPosition();
		position.y = WaterHeightController::GetHeight() + 0.01f;
		transform->SetPosition(position);

		effect->SetWorld(*transform);
		effect->Begin();
		effect->BeginPass(0);

		mesh->Draw(*effect);

		effect->EndPass();
		effect->End();
	}
	else
	{
		transform->SetWorld();
		mesh->Draw();
	}
}
