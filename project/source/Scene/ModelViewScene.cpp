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
#include "../../Framework/Renderer3D/MeshContainer.h"

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
		D3DXVECTOR3 position = { -80.0f, 0.0f, -20.0f * i + 20.0f};

		PlaceActor *actor = new StraightRoadActor(position, (Field::FieldLevel)i, false);
		actorContainer.push_back(actor);
		actor->Rotate(90.0f);
		position.x += OffsetX;

		actorContainer.push_back(new CurveRoadActor(position, (Field::FieldLevel)i, false));
		position.x += OffsetX;

		actorContainer.push_back(new TJunctionActor(position, (Field::FieldLevel)i, false));
		position.x += OffsetX;

		actorContainer.push_back(new CrossJunctionActor(position, (Field::FieldLevel)i, false));
		position.x += OffsetX * 2.0f;

		actorContainer.push_back(new CityActor(position, (Field::FieldLevel)i));
		position.x += OffsetX * 2.0f;

		actorContainer.push_back(new BridgeActor(position, (Field::FieldLevel)i));
		position.x += OffsetX * 2.0f;

		actorContainer.push_back(new MountainActor(position, (Field::FieldLevel)i, false));
		position.x += OffsetX * 2.0f;
	}

	skybox = new Field::FieldSkyBox(Field::FieldLevel::World);
	sceneCamera = new ModelViewCamera();
	Camera::SetMainCamera(sceneCamera);

	//ResourceManager::Instance()->LoadMesh("TestRobo", "data/Robot.x");
	//mesh = new MeshContainer();
	//ResourceManager::Instance()->GetMesh("TestRobo", mesh);
	//meshTransform = new Transform();
	//meshTransform->SetPosition({ -150.0f, 0.0f, 0.0f });
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
	actorContainer.clear();

	SAFE_DELETE(skybox);

	SAFE_DELETE(sceneCamera);

	//SAFE_DELETE(mesh);
	//SAFE_DELETE(meshTransform);
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

	//meshTransform->SetWorld();
	//mesh->Draw();
}
