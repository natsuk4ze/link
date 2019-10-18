//=====================================
//
//GameScene.cpp
//機能:ゲームシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../../Framework/Renderer3D/SkyBox.h"
#include "../FieldObject/Actor/PlaceActor.h"
#include "../Field/FieldController.h"
#include "../Field/Camera/FieldCamera.h"
#include "../../Framework/Renderer2D/TextViewer.h"
#include "../Viewer/GameScene/GameViewer/GameViewer.h"
#include "../Event/EventController.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"

//※イベントコントローラーが出来たらそっち移動
#include "../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../FieldObject/Actor/CrossJunctionActor.h"
#include "../FieldObject/Actor/CityActor.h"

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

	//※イベントコントローラーが出来たらそっち移動
	eventViewer = new EventViewer();

	//ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();

	//ステート初期化
	ChangeState(State::Initialize);

	//testActor = new CityActor(D3DXVECTOR3(150.0f, 0.0f, -150.0f), FModel::City);
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

	//※イベントコントローラーが出来たらそっち移動
	SAFE_DELETE(eventViewer);

	//ステートマシン削除
	Utility::DeleteContainer(fsm);

	//SAFE_DELETE(testActor);
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

	//ビューワパラメータをビューワに渡す
	GameViewerParam param;
	param.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(param);
	gameViewer->ReceiveParam(param);

	//ビュアー更新
	gameViewer->Update();

	//※イベントコントローラーが出来たらそっち移動
	eventViewer->Update();

	//testActor->Update();
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

	//テキストビューワをテスト表示
	static int x = 1650;
	static int y = 950;
	static std::string str = "イベント発生！";
	text->SetText(str);
	text->SetPos(x, y);
	text->Draw();

	//ビュアー描画
	gameViewer->Draw();

	//※イベントコントローラーが出来たらそっち移動
	eventViewer->Draw();

	// イベント描画
	eventController->Draw();
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
