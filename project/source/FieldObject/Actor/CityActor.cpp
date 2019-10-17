//=====================================
//
// シティアクター[CityActor.cpp]
// 機能：都市（国、星）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CityActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"

//=====================================
// コンストラクタ
//=====================================
CityActor::CityActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("Town-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::Town;

	// テスト
	ActorAnimation::RotateAndExpantion(*this);
}

//=====================================
// デストラクタ
//=====================================
CityActor::~CityActor()
{
}
