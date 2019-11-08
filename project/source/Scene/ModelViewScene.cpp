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

	// FieldLevel = City
	ResourceManager::Instance()->LoadMesh("CrossJunction-City", "data/MODEL/PlaceActor/Cross-Junction.x");
	ResourceManager::Instance()->LoadMesh("TJunction-City", "data/MODEL/PlaceActor/T-Junction.x");
	ResourceManager::Instance()->LoadMesh("StraightRoad-City", "data/MODEL/PlaceActor/Straight.x");
	ResourceManager::Instance()->LoadMesh("CurveRoad-City", "data/MODEL/PlaceActor/Curve.x");
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
	ResourceManager::Instance()->LoadMesh("Bridge-City", "data/MODEL/PlaceActor/bridge.x");
	ResourceManager::Instance()->LoadMesh("Mountain-City", "data/MODEL/PlaceActor/mountain.x");
	ResourceManager::Instance()->LoadMesh("River-City", "data/MODEL/PlaceActor/river.x");
	ResourceManager::Instance()->LoadMesh("AlongCity", "data/MODEL/AlongActor/AlongActorCity.x");

	// FieldLevel = World

	// FieldLevel = Space
	ResourceManager::Instance()->LoadMesh("Town-Space", "data/Model/PlaceActor/earth.x");
	ResourceManager::Instance()->LoadMesh("River-Space", "data/Model/PlaceActor/spaceTear.x");

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
