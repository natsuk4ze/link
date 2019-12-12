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
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../Viewer/GameScene/Controller/NameEntryViewer.h"
#include "../../../Framework/Resource/FontManager.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/BackgroundMusic.h"
#include "../../Booth/BoothController.h"

/**************************************
入場処理
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{	
	//ブース制御のシリアル通信開始
	BoothController::Instance()->Init();

	//テキストビューアで使用するフォントをロード
	FontManager::Instance()->LoadFont("data/FONT/Makinas-4-Square.otf");
	FontManager::Instance()->LoadFont("data/FONT/Text_cinecaption226.ttf");
	
	// イベント用モデル
	ResourceManager::Instance()->LoadMesh("Meteor", "data/MODEL/Planet/Meteor.x");
	ResourceManager::Instance()->LoadMesh("UFO", "data/MODEL/UFO/UFO.x");

	// 使用しないUIの描画をOFF（タイトル、リザルト用など）
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	GuideViewer::Instance()->SetActive(false);
	//entity.guideViewer->SetActive(false);
	entity.resultViewer->SetActive(false);
	entity.nemeEntryViewer->SetActive(false);

	//パーティクル初期化
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
	//BGM::Load("data/SOUND/BGM/Course_Select.wav", 0);
	//BGM::FadeIn(0, 0.1f, 30);
	for (int i = 0; i < SoundConfig::VoiceMax; i++)
	{
		SE::Load(SoundConfig::VoicePath[i], SoundConfig::VoiceID(i));
	}
	for (int i = 0; i < SoundConfig::BGMMax; i++)
	{
		BGM::Load(SoundConfig::BGMPath[i], SoundConfig::BGMID(i));
	}

	//制限時間読み込み
	entity.remainTime = PlayerPrefs::GetNumber<int>(Utility::ToString(GameConfig::Key_RemainTime));

	//タイトルに遷移
	entity.ChangeState(State::Title);
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameInit::OnUpdate(GameScene & entity)
{
	entity.field->UpdateObject();
	return GameScene::State::Initialize;
}
