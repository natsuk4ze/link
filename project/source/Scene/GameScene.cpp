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
#include "../../Framework/Renderer2D/TextViewer.h"
#include "../Viewer/GameScene/GameViewer/GameViewer.h"
#include "../Event/EventController.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/GameParticleManager.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "GameState/GameFinish.h"
#include "GameState/GameLevelUp.h"

#include "../FieldObject/Actor/BridgeActor.h"

#include "../../Framework/Tool/DebugWindow.h"

/**************************************
staticメンバ
***************************************/
int GameScene::level = 0;		//デバッグ用フィールドレベル（本番では非staticメンバにする

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	//カメラ作成
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);

	//テキスト用にフォントをロード
	TextViewer::LoadFont("data/FONT/mplus-2c-heavy.ttf");

	//各インスタンス作成
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));
	field = new Field::FieldController();
	text = new TextViewer("M+ 2c heavy", 50);
	gameViewer = new GameViewer();
	eventController = new EventController(Field::Model::City);
	eventController->ReceiveFieldController(field);
	particleManager = GameParticleManager::Instance();

	//ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();
	fsm[State::Finish] = new GameFinish();
	fsm[State::LevelUp] = new GameLevelUp();

	//デリゲートを作成して設定
	onBuildRoad = Delegate<GameScene, Route&>::Create(this, &GameScene::OnBuildRoad);
	field->SetCallbackOnBuildRoad(onBuildRoad);

	//ステート初期化
	ChangeState(State::Initialize);

	//testActor = new BridgeActor(D3DXVECTOR3(150.0f, 0.0f, -150.0f), FModel::City);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	//カメラ削除
	SAFE_DELETE(fieldCamera);

	//フォントをアンインストール
	TextViewer::RemoveFont("data/FONT/mplus-2c-heavy.ttf");

	//インスタンス削除
	SAFE_DELETE(skybox);
	SAFE_DELETE(field);
	SAFE_DELETE(text);
	SAFE_DELETE(gameViewer);
	SAFE_DELETE(eventController);

	//パーティクル終了
	particleManager->Uninit();

	//ステートマシン削除
	Utility::DeleteContainer(fsm);

	//SAFE_DELETE(testActor);
	//デリゲート削除
	SAFE_DELETE(onBuildRoad);

}
#include "../../Framework/Camera/CameraTranslationPlugin.h"
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

	Debug::Begin("Camera");
	if(Debug::Button("Translation")) Camera::TranslationPlugin::Instance()->Move(Vector3::Zero, 30);
	if (Debug::Button("Restore")) Camera::TranslationPlugin::Instance()->Restore(30);
	Debug::End();

	//カメラ更新
	fieldCamera->Update();

	//ビューワパラメータをビューワに渡す
	GameViewerParam param;
	param.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(param);
	gameViewer->ReceiveParam(param);

	//ビュアー更新
	gameViewer->Update();

	//パーティクル更新
	particleManager->Update();
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

	//オブジェクト描画
	field->Draw();

	// イベント描画
	eventController->Draw();

	//パーティクル描画
	particleManager->Draw();

	//テキストビューワをテスト表示
	static int x = 1650;
	static int y = 950;
	static std::string str = "イベント発生！";
	text->SetText(str);
	text->SetPos(x, y);
	text->Draw();

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
