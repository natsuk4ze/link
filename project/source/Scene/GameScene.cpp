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
#include "../FieldObject/PlaceActor.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../Field/FieldController.h"
#include "../Field/Camera/FieldCamera.h"
#include "../../Framework/Renderer2D/TextViewer.h"
#include "../Viewer/GameScene/GameViewer/GameViewer.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	//カメラ作成
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);

	// 3Dオブジェクトのリソースをロード
	ResourceManager::Instance()->LoadMesh("Model", "data/MODEL/PlaceActor/Cross-Junction.x");

	//テキスト用にフォントをロード
	TextViewer::LoadFont("data/FONT/mplus-2c-heavy.ttf");

	//各インスタンス作成
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));
	field = new Field::FieldController();
	text = new TextViewer("M+ 2c heavy", 50);
	gameViewer = new GameViewer();

	//ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();

	//ステート初期化
	ChangeState(State::Initialize);
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

	//ステートマシン削除
	Utility::DeleteContainer(fsm);
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

	//ビュアー更新
	gameViewer->Update();
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
