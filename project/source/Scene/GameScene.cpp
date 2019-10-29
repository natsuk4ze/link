//=====================================
//
//GameScene.cpp
//機能:ゲームシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../GameConfig.h"
#include "../../Framework/Transition/TransitionController.h"
#include "../../Framework/Core/SceneManager.h"

#include "../../Framework/Renderer3D/SkyBox.h"
#include "../FieldObject/Actor/PlaceActor.h"
#include "../Field/FieldController.h"
#include "../Field/Camera/FieldCamera.h"
#include "../Viewer/GameScene/GameViewer/GameViewer.h"
#include "../Event/EventController.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/GameParticleManager.h"
#include "../Field/FieldEventHandler.h"

#include "../../Framework/PostEffect/BloomController.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "GameState/GameFinish.h"
#include "GameState/GameLevelUp.h"
#include "GameState\/GamePause.h"

#include "../../Framework/Tool/DebugWindow.h"

/**************************************
staticメンバ
***************************************/
int GameScene::level = 0;		//デバッグ用フィールドレベル（本番では非staticメンバにする
const float GameScene::BloomPower[] = {0.25f, 0.25f, 0.15f};		//ブルームの強さ
const float GameScene::BloomThrethold[] = {0.45f, 0.5f, 0.55f};		//ブルームをかける輝度の閾値

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	//カメラ作成
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);

	//各インスタンス作成
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));
	field = new Field::FieldController();
	gameViewer = new GameViewer();
	eventController = new EventController(Field::Model::City);
	eventHandler = new FieldEventHandler();
	eventController->ReceiveFieldEventHandler(eventHandler);
	particleManager = GameParticleManager::Instance();
	bloomController = new BloomController();

	//ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();
	fsm[State::Finish] = new GameFinish();
	fsm[State::LevelUp] = new GameLevelUp();
	fsm[State::Pause] = new GamePause();

	//デリゲートを作成して設定
	onBuildRoad = DelegateObject<GameScene, void(Route&)>::Create(this, &GameScene::OnBuildRoad);
	field->SetCallbackOnBuildRoad(onBuildRoad);

	//ステート初期化
	ChangeState(State::Initialize);

	//testActor = new CityActor(D3DXVECTOR3(150.0f, 0.0f, -150.0f), FModel::City);
	std::vector<D3DXVECTOR3> root;
	D3DXVECTOR3 push = D3DXVECTOR3(150.0f, 0.0f, -150.0f);
	root.push_back(push);
	push = D3DXVECTOR3(250.0f, 0.0f, -150.0f);
	root.push_back(push);
	push = D3DXVECTOR3(250.0f, 0.0f, -50.0f);
	root.push_back(push);
	push = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	root.push_back(push);
	passengerController = new PassengerController();
	passengerController->SetPassenger(root);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	//カメラ削除
	SAFE_DELETE(fieldCamera);

	//インスタンス削除
	SAFE_DELETE(skybox);
	SAFE_DELETE(field);
	SAFE_DELETE(gameViewer);
	SAFE_DELETE(eventController);
	SAFE_DELETE(bloomController);

	//パーティクル終了
	particleManager->Uninit();

	//ステートマシン削除
	Utility::DeleteContainer(fsm);

	//SAFE_DELETE(testActor);
	SAFE_DELETE(passengerController);

	//デリゲート削除
	SAFE_DELETE(onBuildRoad);

}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	//ステートを更新
	State next = fsm[currentState]->OnUpdate(*this);

	if (next != currentState)
	{
		ChangeState(next);
	}

	//カメラ更新
	fieldCamera->Update();

	//testActor->Update();
	passengerController->Update();

	//ビューワパラメータをビューワに渡す
	GameViewerParam param;
	param.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(param);
	gameViewer->ReceiveParam(param);

	//ビュアー更新
	gameViewer->Update();

	//パーティクル更新
	particleManager->Update();

	Debug::Begin("EventHandler");
	if (Debug::Button("Pause"))
		eventHandler->PauseGame();
	if (Debug::Button("Resume"))
		eventHandler->ResumeGame();
	if (Debug::Button("GetTownPos"))
		eventHandler->GetNewTownPosition();
	if (Debug::Button("DestroyTown"))
		eventHandler->DestroyTown(eventHandler->GetDestroyTarget());
	Debug::End();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	//カメラセット
	fieldCamera->Set();

	//背景描画
	skybox->Draw();

	//testActor->Draw();
	passengerController->Draw();

	//オブジェクト描画
	field->Draw();

	// イベントオブジェクト描画
	eventController->DrawEventObject();

	//ポストエフェクトは重いのでリリース版のみ適用する
#ifndef _DEBUG
	//ポストエフェクト適用
	bloomController->Draw(renderTexture);
#endif
	//パーティクル描画
	particleManager->Draw();

	// イベントビューア描画
	eventController->DrawEventViewer();

	//ビュアー描画
	gameViewer->Draw();
}

/**************************************
ステート遷移処理
***************************************/
void GameScene::ChangeState(State next)
{
	prevState = currentState;

	currentState = next;

	if (fsm[currentState] != NULL)
	{
		fsm[currentState]->OnStart(*this);
	}
}

/**************************************
イベントコントローラへのPlace受け渡し処理
***************************************/
void GameScene::OnBuildRoad(Route& route)
{
	eventController->CheckEventHappen(route, Field::Model::FieldLevel::City);
}

/**************************************
レベルアップ処理
***************************************/
void GameScene::OnLevelUp()
{
	//テストなのでインクリメントしてしまう
	//本番ではちゃんと制限する
	
	TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
	{
		level++;
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	});
}

/**************************************
イベントハンドラ設定処理
***************************************/
void GameScene::SetEventHandler()
{
	//中断ファンクタ作成
	eventHandler->functerVoid[FieldEventHandler::FuncterID_void::Pause] = [&]()
	{
		ChangeState(State::Pause);
	};

	//再開ファンクタ作成
	eventHandler->functerVoid[FieldEventHandler::FuncterID_void::Resume] = [&]()
	{
		//TODO:中断前のステートへ戻れるようにする
		ChangeState(State::Idle);
	};

	//制限時間回復ファンクタ作成
	eventHandler->functerInt[FieldEventHandler::FuncterID_int::AddTime] = [&](int frame)
	{
		this->remainTime += frame;
	};

	//フィールドコントローラの方でもハンドラ作成
	field->SetEventHandler(*eventHandler);
}
