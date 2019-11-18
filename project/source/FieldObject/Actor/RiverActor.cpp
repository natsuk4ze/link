//=====================================
//
// リバーアクター[RiverActor.cpp]
// 機能：川（時空断裂）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "RiverActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Math/Easing.h"
#include "../../Shader/RiverEffect.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// staticメンバ
//=====================================
const float RiverActor::FlowSpeed = 0.02f;

//=====================================
// コンストラクタ
//=====================================
RiverActor::RiverActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel),
	direction(Forward),
	effect(nullptr)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("River-City", mesh);
		break;
	case Field::World:
		break;
	case Field::Space:
		ResourceManager::Instance()->GetMesh("River-Space", mesh);
		break;
	default:
		break;
	}

	type = Field::Model::River;
	effect = new Field::Actor::RiverEffect();
}

//=====================================
// デストラクタ
//=====================================
RiverActor::~RiverActor()
{
	SAFE_DELETE(effect);
}

//=====================================
// 更新処理
//=====================================
void RiverActor::Update()
{
	PlaceActor::Update();

	D3DXVECTOR3 position = transform->GetPosition();
	position.y = WaterHeightController::GetHeight();
	transform->SetPosition(position);

	switch (direction)
	{
	case FlowDirection::Back:
		uv.y = Math::WrapAround(0.0f, 1.0f, uv.y - FlowSpeed);
		break;

	case FlowDirection::Forward:
		uv.y = Math::WrapAround(0.0f, 1.0f, uv.y + FlowSpeed);
		break;

	case FlowDirection::Right:
		uv.x = Math::WrapAround(0.0f, 1.0f, uv.x + FlowSpeed);
		break;

	case FlowDirection::Left:
		uv.x = Math::WrapAround(0.0f, 1.0f, uv.x - FlowSpeed);
		break;
	}

}

//=====================================
// 描画処理
//=====================================
void RiverActor::Draw()
{
	if (!onCamera)
		return;

	effect->SetWorld(*transform);
	effect->SetUV(uv);
	
	effect->Begin();
	effect->BeginPass(0);

	mesh->Draw(*effect);

	effect->EndPass();
	effect->End();
}

//=====================================
// 流れる方向のセット処理
//=====================================
void RiverActor::SetDirection(FlowDirection direction)
{
	this->direction = direction;
}
