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

//=====================================
// コンストラクタ
//=====================================
MountainActor::MountainActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case FModel::City:
		//ResourceManager::Instance()->GetMesh("Mountain-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::Road;
}

//=====================================
// デストラクタ
//=====================================
MountainActor::~MountainActor()
{
}
