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
#include "../../Field/Camera/Plugin/FieldCameraTranslationPlugin.h"
#include "../../../Framework/Camera/CameraShakePlugin.h"
#include "../../../Framework/PostEffect/BloomController.h"
#include "../../../Framework/Core/PlayerPrefs.h"
#include "../../GameConfig.h"
#include "../../../Framework/Sound/BackgroundMusic.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"

/**************************************
入場処理
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{	
	// イベント用モデル
	ResourceManager::Instance()->LoadMesh("Meteor", "data/MODEL/Planet/Meteor.x");
	ResourceManager::Instance()->LoadMesh("UFO", "data/MODEL/UFO/UFO.x");

	// ゲームシーンで使用するUIの描画をON
	entity.field->SetActive(true);
	entity.gameViewer->SetActive(true);
	entity.guideViewer->SetActive(true);
	// 使用しないUIの描画をOFF（タイトル、リザルト用など）
	entity.resultViewer->SetActive(false);

	//パーティクル初期化
	entity.particleManager->Init();
	entity.levelParticleManager->Init();

	//カメラにプラグインを追加して初期化
	entity.fieldCamera->AddPlugin(FieldCameraTranslationPlugin::Instance());
	entity.fieldCamera->AddPlugin(CameraShakePlugin::Instance());
	FieldCameraTranslationPlugin::Instance()->Init();

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

	//サウンド読み込み
	//NOTE : 今はお試し。本番ではちゃんとタグを用意する
	BGM::Load("data/SOUND/BGM/Course_Select.wav", 0);
	BGM::FadeIn(0, 0.1f, 30);

	//制限時間読み込み
	entity.remainTime = PlayerPrefs::GetNumber<int>(Utility::ToString(GameConfig::Key_RemainTime));

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
	entity.field->UpdateObject();
	return GameScene::State::Initialize;
}
