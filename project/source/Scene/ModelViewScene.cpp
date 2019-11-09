//=====================================
//
//モデルビューシーン処理[ModelViewScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ModelViewScene.h"
#include "../FieldObject/Actor/PlaceActor.h"
#include "../FieldObject/Actor/CityActor.h"
#include "../FieldObject/Actor/BridgeActor.h"
#include "../FieldObject/Actor/CrossJunctionActor.h"
#include "../FieldObject/Actor/CurveRoadActor.h"
#include "../FieldObject/Actor/MountainActor.h"
#include "../FieldObject/Actor/NoneActor.h"
#include "../FieldObject/Actor/RiverActor.h"
#include "../FieldObject/Actor/StraightRoadActor.h"
#include "../FieldObject/Actor/TJunctionActor.h"
#include "../ModelView/ModelViewCamera.h"

#include "../Field/Object/FieldSkyBox.h"

#include "../../Framework/Resource/ResourceManager.h"
#include "../Field/ActorLoader.h"

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void ModelViewScene::Init()
{
	// 3Dオブジェクトのリソースをロード
	ResourceManager::Instance()->LoadMesh("NoneActor", "data/MODEL/PlaceActor/ground.x");

	Field::Actor::ActorLoader loader;
	loader.LoadConfig();
	loader.LoadResource();

	for (int i = 0; i < 3; i++)
	{
		const float OffsetX = 10.0f;
		D3DXVECTOR3 position = { -30.0f, 0.0f, -20.0f * i };

		actorContainer.push_back(new StraightRoadActor(position, (Field::FieldLevel)i));
		position.x += OffsetX;

		actorContainer.push_back(new CurveRoadActor(position, (Field::FieldLevel)i));
		position.x += OffsetX;

		actorContainer.push_back(new TJunctionActor(position, (Field::FieldLevel)i));
		position.x += OffsetX;

		actorContainer.push_back(new CrossJunctionActor(position, (Field::FieldLevel)i));
		position.x += OffsetX;

		actorContainer.push_back(new CityActor(position, (Field::FieldLevel)i));
		position.x += OffsetX;

		actorContainer.push_back(new BridgeActor(position, (Field::FieldLevel)i));
		position.x += OffsetX;

		actorContainer.push_back(new MountainActor(position, (Field::FieldLevel)i));
		position.x += OffsetX;
	}

	skybox = new Field::FieldSkyBox(Field::FieldLevel::World);
	sceneCamera = new ModelViewCamera();
	Camera::SetMainCamera(sceneCamera);
}

/**************************************
終了処理
***************************************/
void ModelViewScene::Uninit()
{
	for (auto&& actor : actorContainer)
	{
		SAFE_DELETE(actor);
	}

	SAFE_DELETE(skybox);

	SAFE_DELETE(sceneCamera);
}

/**************************************
更新処理
***************************************/
void ModelViewScene::Update()
{
	sceneCamera->Update();
}

/**************************************
描画処理
***************************************/
void ModelViewScene::Draw()
{
	sceneCamera->Set();

	skybox->Draw();

	for (auto&& actor : actorContainer)
	{
		actor->Draw();
	}
}
