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
#include "../../Framework/Network/UDPClient.h"
#include "../../Framework/Network/PacketConfig.h"

#include "../GameConfig.h"
#include "../Field/Object/FieldSkyBox.h"
#include "../FieldObject/Actor/PlaceActor.h"
#include "../Field/FieldController.h"
#include "../Field/Camera/FieldCamera.h"
#include "../Viewer/GameScene/Controller/GameViewer.h"
#include "../Event/EventController.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/GameParticleManager.h"
#include "../Field/FieldEventHandler.h"
#include "../Effect/CityParticleManager.h"
#include "../Effect/WorldParticleManager.h"
#include "../Effect/SpaceParticleManager.h"
#include "../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../Viewer/GameScene/Controller/ResultViewer.h"
#include "../Viewer/GameScene/Controller/NameEntryViewer.h"
#include "../Viewer/TitleScene/TitleViewer.h"
#include "../Reward/RewardConfig.h"
#include "../Reward/RewardController.h"
#include "../Reward/RewardNotifier.h"

#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Effect/SpriteEffect.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "GameState/GameFinish.h"
#include "GameState/GameLevelUp.h"
#include "GameState/GamePause.h"
#include "GameState/GameFarView.h"
#include "GameState/GameTitle.h"
#include "GameState/GameResult.h"
#include "GameState\GameTransitionOut.h"
#include "GameState\GameTransitionIn.h"
#include "GameState\GameAchieveResult.h"

#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Sound/BackgroundMusic.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

namespace RC = RewardConfig;

/**************************************
staticメンバ
***************************************/
int GameScene::level = 0;		//デバッグ用フィールドレベル（本番では非staticメンバにする
const float GameScene::BloomPower[] = { 0.6f, 0.55f, 0.50f };		//ブルームの強さ
const float GameScene::BloomThrethold[] = { 0.6f, 0.5f, 0.4f };		//ブルームをかける輝度の閾値
const unsigned char GameScene::AngleTable[3] = { 90, 120, 150 };

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

	particleManager = GameParticleManager::Instance();
	particleManager->Init();

	//各インスタンス作成
	field = new Field::FieldController(level);
	gameViewer = new GameViewer();
	eventController = new EventController(level);
	eventHandler = new FieldEventHandler();
	eventController->ReceiveFieldEventHandler(eventHandler);
	bloomController = new BloomController();
	serial = new SerialWrapper(3);								//TODO:ポート番号を変えられるようにする
	Client = new UDPClient();
	resultViewer = new ResultViewer();
	nemeEntryViewer = new NameEntryViewer();
	titleViewer = new TitleViewer();
	rewardNotifier = new RewardNotifier();

	// ガイドビュアーの初期化
	GuideViewer::Instance()->Init();

	// リワードの作成
	RewardController::Instance()->Create();

	//レベル毎のパーティクルマネージャを選択
	switch (level)
	{
	case Field::City:
		levelParticleManager = CityParticleManager::Instance();
		break;
	case Field::World:
		levelParticleManager = WorldParticleManager::Instance();
		break;
	case Field::Space:
		levelParticleManager = SpaceParticleManager::Instance();
		break;
	default:
		levelParticleManager = nullptr;
		break;
	}

	//ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();
	fsm[State::Finish] = new GameFinish();
	fsm[State::LevelUp] = new GameLevelUp();
	fsm[State::Pause] = new GamePause();
	fsm[State::FarView] = new GameFarView();
	fsm[State::Title] = new GameTitle();
	fsm[State::Result] = new GameResult();
	fsm[State::TransitionOut] = new GameTransitionOut();
	fsm[State::TransitionIn] = new GameTransitionIn();
	fsm[State::AchieveResult] = new GameAchieveResult();

	//デリゲートを作成して設定
	auto onBuildRoad = std::bind(&GameScene::OnBuildRoad, this, std::placeholders::_1);
	field->SetCallbackBuildRoad(onBuildRoad);

	//ステート初期化
	ChangeState(State::Initialize);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	// リワード全削除
	RewardController::Instance()->AllDelete();

	//カメラ削除
	SAFE_DELETE(fieldCamera);

	//インスタンス削除
	SAFE_DELETE(field);
	SAFE_DELETE(gameViewer);
	SAFE_DELETE(eventController);
	SAFE_DELETE(bloomController);
	SAFE_DELETE(eventHandler);
	SAFE_DELETE(serial);
	SAFE_DELETE(Client);
	//SAFE_DELETE(guideViewer);
	SAFE_DELETE(resultViewer);
	SAFE_DELETE(nemeEntryViewer);
	SAFE_DELETE(titleViewer);
	SAFE_DELETE(rewardNotifier);

	// ガイドビュアーの削除
	GuideViewer::Instance()->Uninit();

	//パーティクル終了
	particleManager->Uninit();

	if (levelParticleManager != nullptr)
		levelParticleManager->Uninit();

	//ステートマシン削除
	Utility::DeleteContainer(fsm);
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	ProfilerCPU::Instance()->BeginLabel("GameScene");

	//ステートを更新
	State next = fsm[currentState]->OnUpdate(*this);

#ifdef _DEBUG
	//imguiが使えないのでdebug用に使ってます（おーはま）
	if (Keyboard::GetTrigger(DIK_R))
	{
		ChangeState(State::Result);
	}
#endif

	//カメラ更新
	ProfilerCPU::Instance()->Begin("Update Camera");
	fieldCamera->Update();
	ProfilerCPU::Instance()->End("Update Camera");

	//カメラの情報をエフェクトに渡す
	SpriteEffect::SetView(fieldCamera->GetViewMtx());
	SpriteEffect::SetProjection(fieldCamera->GetProjectionMtx());

	//ビューワパラメータをビューワに渡す
	GameViewerParam gameParam;
	gameParam.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(gameParam);
	gameViewer->ReceiveParam(gameParam);

	// イベントビューアに必要なパラメータを渡す
	EventViewerParam eventParam;
	eventController->EmbedViewerParam(eventParam);

	//ビュアー更新
	gameViewer->Update();
	GuideViewer::Instance()->Update();
	resultViewer->Update();
	nemeEntryViewer->Update();
	titleViewer->Update();
	rewardNotifier->Update();

	//パーティクル更新
	ProfilerCPU::Instance()->Begin("Update Particle");

	if (levelParticleManager != nullptr)
		levelParticleManager->Update();

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
	Camera::MainCamera()->Set();

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

	//フィールドの情報表示
	field->DrawInfo();

	//パーティクル描画
	ProfilerCPU::Instance()->Begin("Draw Particle");

	if (levelParticleManager != nullptr)
		levelParticleManager->Draw();

	particleManager->Draw();
	ProfilerCPU::Instance()->End("Draw Particle");

	//ビュアー描画
	Client->Draw();
	field->DrawViewer();
	gameViewer->Draw();
	eventController->DrawEventViewer();
	resultViewer->Draw();
	nemeEntryViewer->Draw();
	titleViewer->Draw();
	rewardNotifier->Draw();

	//*******別ウインドウを作成するため最後*******
	GuideViewer::Instance()->Draw();

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
	bool flgPause = eventController->CheckEventHappen(route, level);

	if (flgPause)
		ChangeState(State::Pause);
}

/**************************************
レベルアップ処理
***************************************/
void GameScene::OnLevelUp()
{
	//現在の制限時間を保存
	PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_RemainTime), remainTime);

	//BGMをフェードアウト
	BGM::Fade(0.0f, 30, true);

	//テストなのでインクリメントしてしまう
	//本番ではちゃんと制限する
	level++;
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
		level = 0;
		Clear();
		SetFieldLevel(level);
		field->Load();
		ChangeState(Idle);
	}
	Debug::SameLine();
	if (Debug::Button("WorldLevel"))
	{
		level = 1;
		Clear();
		SetFieldLevel(level);
		field->Load();
		ChangeState(Idle);
	}
	Debug::SameLine();
	if (Debug::Button("SpaceLevel"))
	{
		level = 2;
		Clear();
		SetFieldLevel(level);
		field->Load();
		ChangeState(Idle);
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
	if (Debug::Button("Declease Time"))
	{
		remainTime -= 30 * 10;
	}

	Debug::NewLine();
	if (Debug::Button("SendPacket"))
	{
		UDPClient::SendRankPacket("000102","123456789");
	}
	Debug::SameLine();
	if (Debug::Button("GetLastScore"))
	{
		Client->GetLastScore();
	}

	Debug::Text("State");
	Debug::NewLine();
	if (Debug::Button("Title"))
	{
		level = 0;
		ChangeState(State::Title);
	}
	Debug::SameLine();
	if (Debug::Button("Idle"))
	{
		level = 1;
		ChangeState(State::Idle);
	}
	Debug::SameLine();
	if (Debug::Button("Result"))
	{
		level = 2;
		ChangeState(State::Result);
	}
	Debug::SameLine();
	if (Debug::Button("levelup"))
	{
		level++;
		ChangeState(State::TransitionOut);
	}


	Debug::NewLine();
	Debug::Text("Event");
	bool flgPause = eventController->EventDebug(level);
	if (flgPause)
	{
		ChangeState(Pause);
	}

	Debug::NewLine();
	Debug::Text("Bloom");
	static D3DXVECTOR3 power = { BloomPower[0], BloomPower[1], BloomPower[2] };
	static D3DXVECTOR3 threthold = { BloomThrethold[0], BloomThrethold[1], BloomThrethold[2] };
	Debug::Slider("power", power, Vector3::Zero, Vector3::One);
	Debug::Slider("threthold", threthold, Vector3::Zero, Vector3::One);
	bloomController->SetPower(power.x, power.y, power.z);
	bloomController->SetThrethold(threthold.x, threthold.y, threthold.z);

	Debug::NewLine();
	Debug::Text("Achieve");
	Debug::CheckBox("Use DebugAchieve", debugReward);
	for (int i = 0; i < 10; i += 2)
	{
	}

	Debug::End();
}

/**************************************
フィールドレベル設定処理
***************************************/
void GameScene::SetFieldLevel(int level)
{
	LARGE_INTEGER start, end;

	//フィールドレベルを設定
	field->SetLevel((Field::FieldLevel)level);

	// フィールドレベルアップパケットを送信
	UDPClient::SendLevelUpPacket();

	//レベル固有のパーティクルマネージャ初期化
	start = ProfilerCPU::GetCounter();
	switch (level)
	{
	case Field::City:
		levelParticleManager = CityParticleManager::Instance();
		break;
	case Field::World:
		levelParticleManager = WorldParticleManager::Instance();
		break;
	case Field::Space:
		levelParticleManager = SpaceParticleManager::Instance();
		break;
	default:
		levelParticleManager = nullptr;
		break;
	}
	levelParticleManager->Init();

	end = ProfilerCPU::GetCounter();

	Debug::Log("Init Particle : %f", ProfilerCPU::CalcElapsed(start, end));

	start = ProfilerCPU::GetCounter();

	//イベントコントローラ作成
	eventController->Init(level);

	//イベントハンドラ設定
	SetEventHandler();

	end = ProfilerCPU::GetCounter();

	Debug::Log("Init Event : %f", ProfilerCPU::CalcElapsed(start, end));
}

/**************************************
シーンクリア処理
***************************************/
void GameScene::Clear()
{
	LARGE_INTEGER start, end;

	//フィールド側をクリア
	start = ProfilerCPU::GetCounter();
	field->Clear();
	end = ProfilerCPU::GetCounter();

	Debug::Log("Clear Field : %f", ProfilerCPU::CalcElapsed(start, end));

	//イベントコントローラクリア
	start = ProfilerCPU::GetCounter();
	eventController->Uninit();
	end = ProfilerCPU::GetCounter();

	Debug::Log("Clear Event : %f", ProfilerCPU::CalcElapsed(start, end));

	//レベル固有のパーティクルを終了
	start = ProfilerCPU::GetCounter();
	levelParticleManager->Uninit();
	levelParticleManager = nullptr;
	end = ProfilerCPU::GetCounter();

	Debug::Log("Clear Particle : %f", ProfilerCPU::CalcElapsed(start, end));

	//イベントコントローラクリア
	start = ProfilerCPU::GetCounter();
	eventController->Uninit();
	end = ProfilerCPU::GetCounter();

	Debug::Log("Clear Event : %f", ProfilerCPU::CalcElapsed(start, end));

	// リワードをリセット
	rewardNotifier->ResetAchieved();
	RewardController::Instance()->ResetAllRewardData();
}
