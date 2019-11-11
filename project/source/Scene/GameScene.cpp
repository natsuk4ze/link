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
#include "../../Framework/Tool/ProfilerCPU.h"
#include "../../Framework/Core/PlayerPrefs.h"
#include "../../Framework/Serial/SerialWrapper.h"

#include "../GameConfig.h"
#include "../Field/Object/FieldSkyBox.h"
#include "../FieldObject/Actor/PlaceActor.h"
#include "../Field/FieldController.h"
#include "../Field/Camera/FieldCamera.h"
#include "../Viewer/GameScene/GameViewer/GameViewer.h"
#include "../Event/EventController.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/GameParticleManager.h"
#include "../Field/FieldEventHandler.h"

#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Effect/SpriteEffect.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "GameState/GameFinish.h"
#include "GameState/GameLevelUp.h"
#include "GameState/GamePause.h"
#include "GameState/GameFarView.h"

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

	//フィールドレベル読み込み
	Field::FieldLevel level = (Field::FieldLevel)PlayerPrefs::GetNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel));

	//各インスタンス作成
	field = new Field::FieldController(level);
	gameViewer = new GameViewer();
	eventController = new EventController(level);
	eventHandler = new FieldEventHandler();
	eventController->ReceiveFieldEventHandler(eventHandler);
	particleManager = GameParticleManager::Instance();
	bloomController = new BloomController();
	//serial = new SerialWrapper(3);								//TODO:ポート番号を変えられるようにする

	//ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();
	fsm[State::Finish] = new GameFinish();
	fsm[State::LevelUp] = new GameLevelUp();
	fsm[State::Pause] = new GamePause();
	fsm[State::FarView] = new GameFarView();

	//デリゲートを作成して設定
	onBuildRoad = DelegateObject<GameScene, void(Route&)>::Create(this, &GameScene::OnBuildRoad);
	field->SetCallbackOnBuildRoad(onBuildRoad);

	//ステート初期化
	ChangeState(State::Initialize);

	// テスト用
	//testInfoController = new InfoController();
	//testInfoController->SetLinkLevel(Field::FieldPosition(16, 16), 100);
	//testInfoController->SetLinkLevel(Field::FieldPosition(17, 17), 90);
	//testInfoController->SetLinkLevel(Field::FieldPosition(29, 29), 99);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	//カメラ削除
	SAFE_DELETE(fieldCamera);

	//インスタンス削除
	SAFE_DELETE(field);
	SAFE_DELETE(gameViewer);
	SAFE_DELETE(eventController);
	SAFE_DELETE(bloomController);
	SAFE_DELETE(eventHandler);
	//SAFE_DELETE(serial);

	//パーティクル終了
	particleManager->Uninit();

	//ステートマシン削除
	Utility::DeleteContainer(fsm);

	// テスト用
	//SAFE_DELETE(testInfoController);

	//デリゲート削除
	SAFE_DELETE(onBuildRoad);

}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	ProfilerCPU::Instance()->BeginLabel("GameScene");

	//ステートを更新
	State next = fsm[currentState]->OnUpdate(*this);

	//カメラ更新
	ProfilerCPU::Instance()->Begin("Update Camera");
	fieldCamera->Update();
	ProfilerCPU::Instance()->End("Update Camera");

	//カメラの情報をエフェクトに渡す
	SpriteEffect::SetView(fieldCamera->GetViewMtx());
	SpriteEffect::SetProjection(fieldCamera->GetProjectionMtx());

	// テスト用
	//testInfoController->Update();

	//ビューワパラメータをビューワに渡す
	GameViewerParam gameParam;
	gameParam.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(gameParam);
	gameViewer->ReceiveParam(gameParam);

	EventViewerParam eventParam;
	eventController->EmbedViewerParam(eventParam);

	//ビュアー更新
	gameViewer->Update();

	//パーティクル更新
	ProfilerCPU::Instance()->Begin("Update Particle");
	particleManager->Update();
	ProfilerCPU::Instance()->End("Update Particle");

	//デバッグ機能
	DebugTool();

	Debug::Begin("EventHandler");
	if (Debug::Button("Pause"))
		eventHandler->PauseGame();
	if (Debug::Button("Resume"))
		eventHandler->ResumeGame();
	if (Debug::Button("GetTownPos"))
		eventHandler->GetNewTownPosition();
	if (Debug::Button("DestroyTown"))
		eventHandler->DestroyTown(eventHandler->GetDestroyTarget());
	if (Debug::Button("CreateTown"))
		eventHandler->CreateNewTown(eventHandler->GetNewTownPosition());
	Debug::End();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	//カメラセット
	fieldCamera->Set();

	// テスト用

	//オブジェクト描画
	ProfilerCPU::Instance()->Begin("Draw Object");
	field->Draw();
	ProfilerCPU::Instance()->End("Draw Object");

	// イベントオブジェクト描画
	ProfilerCPU::Instance()->Begin("Draw Event");
	eventController->DrawEventObject();
	ProfilerCPU::Instance()->End("Draw Event");

	//testInfoController->Draw();

	//ポストエフェクトは重いのでリリース版のみ適用する
#ifndef _DEBUG
	//ポストエフェクト適用
	ProfilerCPU::Instance()->Begin("Draw PostEffect");
	bloomController->Draw(renderTexture);
	ProfilerCPU::Instance()->End("Draw PostEffect");
#endif

	//パーティクル描画
	ProfilerCPU::Instance()->Begin("Draw Particle");
	particleManager->Draw();
	ProfilerCPU::Instance()->End("Draw Particle");

	//ビュアー描画
	field->DrawViewer();
	gameViewer->Draw();
	eventController->DrawEventViewer();

	ProfilerCPU::Instance()->EndLabel();
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
	eventController->CheckEventHappen(route, Field::FieldLevel::City);
}

/**************************************
レベルアップ処理
***************************************/
void GameScene::OnLevelUp()
{
	//現在の制限時間を保存
	PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_RemainTime), remainTime);

	//テストなのでインクリメントしてしまう
	//本番ではちゃんと制限する
	TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
	{
		level++;
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), level);
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

/**************************************
デバッグ機能
***************************************/
void GameScene::DebugTool()
{
	//デバッグ機能
	Debug::Begin("DebugTool");
	Debug::Text("Level");
	if (Debug::Button("CityLevel"))
	{
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), Field::FieldLevel::City);
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	}
	if (Debug::Button("WorldLevel"))
	{
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), Field::FieldLevel::World);
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	}
	if (Debug::Button("SpaceLevel"))
	{
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), Field::FieldLevel::Space);
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	}

	Debug::NewLine();
	if (Debug::Button("All Reset"))
	{
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), Field::FieldLevel::City);
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_RemainTime), 30 * 180);
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	}

	Debug::NewLine();
	if (Debug::Button("Add Time"))
	{
		remainTime += 30 * 10;
	}

	Debug::End();
}
