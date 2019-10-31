//=====================================
//
//GameInit.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameInit.h"
#include "../../../Framework/Renderer3D/SkyBox.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Field/FieldController.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../../Framework/Camera/CameraShakePlugin.h"
#include "../../../Framework/PostEffect/BloomController.h"

/**************************************
入場処理
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{
	//スカイボックスのテクスチャをロード
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_up.png", SkyBox::Surface::Up);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_back.png", SkyBox::Surface::Back);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_down.jpg", SkyBox::Surface::Down);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_front.png", SkyBox::Surface::Front);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_left.png", SkyBox::Surface::Left);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_right.png", SkyBox::Surface::Right);

	// 3Dオブジェクトのリソースをロード
	ResourceManager::Instance()->LoadMesh("NoneActor", "data/MODEL/PlaceActor/ground.x");
	// イベント用モデル

	// FieldLevel = City
	ResourceManager::Instance()->LoadMesh("CrossJunction-City", "data/MODEL/PlaceActor/Cross-Junction.x");
	ResourceManager::Instance()->LoadMesh("TJunction-City", "data/MODEL/PlaceActor/T-Junction.x");
	ResourceManager::Instance()->LoadMesh("StraightRoad-City", "data/MODEL/PlaceActor/Straight.x");
	ResourceManager::Instance()->LoadMesh("CurveRoad-City", "data/MODEL/PlaceActor/Curve.x");
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
	ResourceManager::Instance()->LoadMesh("Bridge-City", "data/MODEL/PlaceActor/bridge.x");
	ResourceManager::Instance()->LoadMesh("Mountain-City", "data/MODEL/PlaceActor/mountain.x");
	ResourceManager::Instance()->LoadMesh("River-City", "data/MODEL/PlaceActor/river.x");
	ResourceManager::Instance()->LoadMesh("Car", "data/MODEL/PassengerActor/ToonCar.x");
	ResourceManager::Instance()->MakePolygon("LinkInfo", "data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png", D3DXVECTOR2(3.0f, 5.0f), D3DXVECTOR2(4.0f, 3.0f));

	// FieldLevel = World

	// FieldLevel = Space

	//パーティクル初期化
	entity.particleManager->Init();

	//カメラにプラグインを追加して初期化
	entity.fieldCamera->AddPlugin(Camera::TranslationPlugin::Instance());
	entity.fieldCamera->AddPlugin(Camera::ShakePlugin::Instance());
	Camera::TranslationPlugin::Instance()->Init();

	//カメラの追従目標にカーソルを設定してモード切替
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

	//CSVデータをロード
	entity.field->Load();

	//イベントハンドラ設定
	entity.SetEventHandler();

	//ブルームエフェクトのパラメータ設定
	entity.bloomController->SetPower(entity.BloomPower[0], entity.BloomPower[1], entity.BloomPower[2]);
	entity.bloomController->SetThrethold(entity.BloomThrethold[0], entity.BloomThrethold[1], entity.BloomThrethold[2]);

	//制限時間読み込み
	//TODO:シーンを跨いで引き継ぐようにする
	entity.remainTime = 30 * 180;

	//トランジション画面をオフにして遷移
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]()
	{
		entity.ChangeState(State::Idle);
	});
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameInit::OnUpdate(GameScene & entity)
{
	return GameScene::State::Initialize;
}
