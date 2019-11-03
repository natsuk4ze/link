//=====================================
//
//パーティクルテストシーン処理[ParticleTestScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ParticleTestScene.h"
#include "../../Framework/Renderer3D/SkyBox.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../Field/Object/FieldGround.h"
#include "../Effect/TestParticleCamera.h"
#include "../FieldObject/Actor/CityActor.h"
#include "../FieldObject/Actor/MountainActor.h"
#include "../FieldObject/Actor/RiverActor.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/TestParticleManager.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Effect/SpriteEffect.h"
#include "../Field/Object/FieldSkyBox.h"

/**************************************
初期化処理
***************************************/
void ParticleTestScene::Init()
{
	//インスタンス作成
	skybox = new Field::FieldSkyBox(Field::FieldLevel::Space);
	ground = new Field::FieldGround();
	sceneCamera = new TestParticleCamera();
	particleManager = TestParticleManager::Instance();
	bloom = new BloomController();

	//アクターのモデルをロード
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
	ResourceManager::Instance()->LoadMesh("Mountain-City", "data/MODEL/PlaceActor/mountain.x");
	ResourceManager::Instance()->LoadMesh("River-City", "data/MODEL/PlaceActor/river.x");
	actor = new CityActor(Vector3::Zero, Field::FieldLevel::City);
	//actor = new MountainActor(Vector3::Zero, Field::FieldLevel::City);
	//actor = new RiverActor(Vector3::Zero, Field::FieldLevel::City);
	//actor->SetScale(Vector3::One * 1.0f);

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
	//ground->Draw();

	static bool drawableActor = true;
	
	Debug::Begin("DrawActor");
	if (Debug::Button("Switch"))
		drawableActor = !drawableActor;
	Debug::End();

	if(drawableActor)
		actor->Draw();

	bloom->Draw(renderTexture);

	particleManager->Draw();
}
