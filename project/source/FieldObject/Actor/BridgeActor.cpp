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
BridgeActor::BridgeActor()
	: PlaceActor(),
	effect(nullptr),
	uv(0.0f, 0.0f),
	level(Field::FieldLevel::City)
{
	effect = new Field::Actor::RiverEffect();

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
// 初期化処理
//=====================================
void BridgeActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::BridgeTag[currentLevel].c_str(), mesh);
	
	level = currentLevel;

	PlaceActor::Init(pos, currentLevel);
}

//=====================================
// 更新処理
//=====================================
void BridgeActor::Update()
{
	PlaceActor::Update();

	if (level == Field::FieldLevel::Space)
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
	if (level != Field::FieldLevel::Space)
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