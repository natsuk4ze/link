//=====================================
//
// ブリッジアクター[BridgeActor.cpp]
// 機能：橋（ワープホール）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "BridgeActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Shader/RiverEffect.h"

//=====================================
// コンストラクタ
//=====================================
BridgeActor::BridgeActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel),
	effect(nullptr),
	uv(0.0f, 0.0f)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::BridgeTag[currentLevel].c_str(), mesh);

	if (currentLevel == Field::FieldLevel::Space)
	{
		effect = new Field::Actor::RiverEffect();
	}

	type = Field::Model::Bridge;
}

//=====================================
// デストラクタ
//=====================================
BridgeActor::~BridgeActor()
{
	SAFE_DELETE(effect);
}

//=====================================
// 更新処理
//=====================================
void BridgeActor::Update()
{
	PlaceActor::Update();

	if (effect != nullptr)
	{
		uv.y += 0.005f;
		effect->SetUV(uv);
	}
}

//=====================================
// 描画処理
//=====================================
void BridgeActor::Draw()
{
	if (effect == nullptr)
	{
		PlaceActor::Draw();
	}
	else
	{
		if (!this->IsActive())
			return;

		if (!onCamera)
			return;

		effect->Begin();
		effect->BeginPass(0);

		effect->SetWorld(*transform);
		mesh->Draw(*effect);

		effect->EndPass();
		effect->End();
	}
}