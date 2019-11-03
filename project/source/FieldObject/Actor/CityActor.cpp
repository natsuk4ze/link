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
CityActor::CityActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("Town-City", mesh);
		break;
	case Field::World:
		break;
	case Field::Space:
		ResourceManager::Instance()->GetMesh("Town-Space", mesh);
		break;
	default:
		break;
	}

	type = Field::Model::Town;
}

//=====================================
// デストラクタ
//=====================================
CityActor::~CityActor()
{
}
