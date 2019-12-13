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
#include "../../../Framework/Renderer3D/MophingMeshContainer.h"

#define USE_MORPHING

//=====================================
// コンストラクタ
//=====================================
CityActor::CityActor()
	: PlaceActor(),
	inMorphing(false),
	cntFrameMorphing(0)
{
	type = Field::Model::Town;
	morphContainer = new MorphingMeshContainer();
}

//=====================================
// デストラクタ
//=====================================
CityActor::~CityActor()
{
	SAFE_DELETE(morphContainer);
}

//=====================================
// 初期化処理
//=====================================
void CityActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel)
{
	using Field::Actor::ActorLoader;

#ifdef USE_MORPHING
	switch (currentLevel)
	{
	case Field::FieldLevel::City:
		for (int i = 0; i < 3; i++)
		{
			ResourceManager::Instance()->GetMesh(ActorLoader::CityTownTag[i].c_str(), morphContainer);
			morphContainer->RegisterVertex(i);
		}
		morphContainer->SetCurrent(0);
		morphContainer->SetNext(1);
		useMorphing = true;
		break;

	case Field::FieldLevel::World:
		for (int i = 0; i < 3; i++)
		{
			ResourceManager::Instance()->GetMesh(ActorLoader::WorldTownTag[i].c_str(), morphContainer);
			morphContainer->RegisterVertex(i);
		}
		morphContainer->SetCurrent(0);
		morphContainer->SetNext(1);
		useMorphing = true;
		break;

	case Field::FieldLevel::Space:
		ResourceManager::Instance()->GetMesh(ActorLoader::CityTag[currentLevel].c_str(), mesh);
		useMorphing = false;
		break;
	}
#else
	ResourceManager::Instance()->GetMesh(ActorLoader::CityTag[currentLevel].c_str(), mesh);
#endif

	PlaceActor::Init(pos, currentLevel);
}

//=====================================
// 終了処理
//=====================================
void CityActor::Uninit()
{
	morphContainer->ReleaseRegistration();
	PlaceActor::Uninit();
}

//=====================================
// 描画処理
//=====================================
void CityActor::Draw()
{
	if (useMorphing)
	{
		cntFrameMorphing = Math::WrapAround(0, 60, ++cntFrameMorphing);

		float t = (float)cntFrameMorphing / 60;

		morphContainer->SetChange(t);
		morphContainer->Draw(transform->GetMatrix());
	}
	else
	{
		PlaceActor::Draw();
	}
}

//=====================================
// モーフィング開始
//=====================================
void CityActor::StartMorph(int next)
{
}
