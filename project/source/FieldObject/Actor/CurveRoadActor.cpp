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

//=====================================
// コンストラクタ
//=====================================
CurveRoadActor::CurveRoadActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("CurveRoad-City", mesh);
		break;
	case Field::World:
		break;
	case Field::Space:
		break;
	default:
		break;
	}

	type = Field::Model::Road;
}

//=====================================
// デストラクタ
//=====================================
CurveRoadActor::~CurveRoadActor()
{
}
