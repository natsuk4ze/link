//=====================================
//
//パーティクルテストシーン処理[ParticleTestScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ParticleTestScene.h"
#include "../../Framework/Renderer3D/SkyBox.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../Field/FieldGround.h"
#include "../Effect/TestParticleCamera.h"
#include "../FieldObject/Actor/CityActor.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/TestParticleManager.h"

/**************************************
初期化処理
***************************************/
void ParticleTestScene::Init()
{
	//インスタンス作成
	skybox = new SkyBox(Vector3::One * 10000.0f);
	ground = new Field::FieldGround();
	sceneCamera = new TestParticleCamera();
	particleManager = TestParticleManager::Instance();

	//スカイボックスのテクスチャロード
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_up.png", SkyBox::Surface::Up);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_back.png", SkyBox::Surface::Back);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_down.jpg", SkyBox::Surface::Down);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_front.png", SkyBox::Surface::Front);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_left.png", SkyBox::Surface::Left);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_right.png", SkyBox::Surface::Right);

	//アクターのモデルをロード
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
	actor = new CityActor(Vector3::Zero, Field::Model::FieldLevel::City);

	//カメラ設定
	Camera::SetMainCamera(sceneCamera);

	//パーティクル初期化
	particleManager->Init();
}

/**************************************
終了処理
***************************************/
void ParticleTestScene::Uninit()
{
	//インスタンス削除
	SAFE_DELETE(skybox);
	SAFE_DELETE(ground);
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(actor);

	//パーティクル削除
	particleManager->Uninit();
}

/**************************************
更新処理
***************************************/
void ParticleTestScene::Update()
{
	sceneCamera->Update();

	particleManager->Update();
}

/**************************************
描画処理
***************************************/
void ParticleTestScene::Draw()
{
	sceneCamera->Set();

	skybox->Draw();
	ground->Draw();
	actor->Draw();

	particleManager->Draw();
}
