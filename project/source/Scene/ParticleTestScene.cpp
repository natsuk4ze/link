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
#include "../FieldObject/Actor/MountainActor.h"
#include "../FieldObject/Actor/RiverActor.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/TestParticleManager.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Effect/SpriteEffect.h"
#include "../Event/EventActor.h"

const D3DXVECTOR3 Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);

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
	bloom = new BloomController();

	//スカイボックスのテクスチャロード
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_up.png", SkyBox::Surface::Up);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_back.png", SkyBox::Surface::Back);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_down.jpg", SkyBox::Surface::Down);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_front.png", SkyBox::Surface::Front);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_left.png", SkyBox::Surface::Left);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_right.png", SkyBox::Surface::Right);

	//アクターのモデルをロード
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
	ResourceManager::Instance()->LoadMesh("Mountain-City", "data/MODEL/PlaceActor/mountain.x");
	ResourceManager::Instance()->LoadMesh("River-City", "data/MODEL/PlaceActor/river.x");
	ResourceManager::Instance()->LoadMesh("UFO", "data/MODEL/UFO/UFO.x");
	actor = new CityActor(Vector3::Zero, Field::Model::FieldLevel::City);
	//actor = new MountainActor(Vector3::Zero, Field::Model::FieldLevel::City);
	//actor = new RiverActor(Vector3::Zero, Field::Model::FieldLevel::City);
	//actor->SetScale(Vector3::One * 1.0f);
	eventActor = new EventActor(Vector3::Up * 10.0f, Scale, "UFO");
	eventActor->SetHoverMotion(true);

	//カメラ設定
	Camera::SetMainCamera(sceneCamera);

	//パーティクル初期化
	particleManager->Init();

	//ブルーム初期化
	bloom->SetPower(0.25f, 0.25f, 0.25f);
	bloom->SetThrethold(0.45f, 0.5f, 0.55f);
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
	SAFE_DELETE(eventActor);
	SAFE_DELETE(bloom);

	//パーティクル削除
	particleManager->Uninit();
}

/**************************************
更新処理
***************************************/
void ParticleTestScene::Update()
{
	Debug::Begin("ActorRot");
	static float angle = 0.0f;
	Debug::Slider("Angle", angle, 0.0f, 360.0f);
	actor->SetRotatition(Vector3::Up * angle);
	Debug::End();

	eventActor->Update();

	sceneCamera->Update();

	particleManager->Update();
}

/**************************************
描画処理
***************************************/
void ParticleTestScene::Draw()
{
	sceneCamera->Set();

	SpriteEffect::SetView(sceneCamera->GetViewMtx());
	SpriteEffect::SetProjection(sceneCamera->GetProjectionMtx());

	skybox->Draw();
	ground->Draw();

	static bool drawableActor = false;
	static bool DrawEventActor = true;

	Debug::Begin("DrawActor");
	if (Debug::Button("DrawPlaceActor"))
		drawableActor = !drawableActor;
	if (Debug::Button("DrawEventActor"))
		DrawEventActor = !DrawEventActor;
	Debug::End();

	if (drawableActor)
		actor->Draw();

	if (DrawEventActor)
		eventActor->Draw();

	bloom->Draw(renderTexture);

	particleManager->Draw();
}
