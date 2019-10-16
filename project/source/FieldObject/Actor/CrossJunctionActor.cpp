//=====================================
//
// クロスジャンクションアクター[CrossJunctionActor.cpp]
// 機能：十字路3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CrossJunctionActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "State/CreateActorState.h"
#include "../Animation/ActorAnimation.h"

//=====================================
// コンストラクタ
//=====================================
CrossJunctionActor::CrossJunctionActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("CrossJunction-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::Junction;

	// テスト
	state = new CreateActorState();
	state->OnStart(*this);
	ActorAnimation::RotateAndExpantion(*this, [&] 
	{
		current = Idle;
	});

}

//=====================================
// デストラクタ（メッシュの開放は基底クラスで）
//=====================================
CrossJunctionActor::~CrossJunctionActor()
{
}
