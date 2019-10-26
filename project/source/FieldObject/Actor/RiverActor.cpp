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

//=====================================
// staticメンバ
//=====================================
const int RiverActor::AnimationPeriod = 360;
const float RiverActor::MaxWaveHeight = 0.015f;
float RiverActor::heightWave = 0.0f;
int RiverActor::cntWaveAnimation = 0;

//=====================================
// コンストラクタ
//=====================================
RiverActor::RiverActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("River-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::River;
}

//=====================================
// デストラクタ
//=====================================
RiverActor::~RiverActor()
{
}

//=====================================
// 更新処理
//=====================================
void RiverActor::Update()
{
	PlaceActor::Update();

	transform->Move(Vector3::Up * heightWave);
}

//=====================================
// 高さの更新処理
//=====================================
void RiverActor::UpdateHeight()
{
	cntWaveAnimation = Math::WrapAround(0, AnimationPeriod, ++cntWaveAnimation);

	float startHeight = (cntWaveAnimation < AnimationPeriod / 2) ? -MaxWaveHeight : MaxWaveHeight;
	float goalHeight = startHeight * -1.0f;
	float t = (cntWaveAnimation < AnimationPeriod / 2) ? cntWaveAnimation / (AnimationPeriod * 0.5f) : (cntWaveAnimation - AnimationPeriod * 0.5f) / (AnimationPeriod * 0.5f);

	heightWave = Easing::EaseValue(t, startHeight, goalHeight, EaseType::InOutBack);
}
