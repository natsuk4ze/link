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
#include "../../Field/ActorLoader.h"

//=====================================
// コンストラクタ
//=====================================
CityActor::CityActor()
	: PlaceActor()
{
	type = Field::Model::Town;
}

//=====================================
// デストラクタ
//=====================================
CityActor::~CityActor()
{
}

//=====================================
// 初期化処理
//=====================================
void CityActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::CityTag[currentLevel].c_str(), mesh);

	PlaceActor::Init(pos, currentLevel);
}
