//=====================================
//
//GameMain.cpp
//機能:ゲームメイン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameMain.h"
#include "../Framework/Core/SceneManager.h"
#include "../Framework/Tool/DebugWindow.h"
#include "../Framework/Core/PlayerPrefs.h"
#include "../Framework/Resource/FontManager.h"

#include "GameConfig.h"

#include "Scene\GameScene.h"
#include "Scene/ParticleTestScene.h"
#include "Scene/ModelViewScene.h"
#include "Scene\MophingTestScene.h"

/**************************************
コンストラクタ
***************************************/
GameMain::GameMain(HINSTANCE hInstance, HWND hWnd) :
	BaseGame(hInstance, hWnd)
{
	//シーンマネージャにシーンのインスタンスを追加
	sceneManager->Add(GameConfig::SceneID::Game, new GameScene(renderTexture, renderSurface));
	sceneManager->Add(GameConfig::SceneID::ParticleTest, new ParticleTestScene(renderTexture, renderSurface));
	sceneManager->Add(GameConfig::SceneID::ModelView, new ModelViewScene(renderTexture, renderSurface));
	sceneManager->Add(GameConfig::SceneID::MophingTest, new MophingTestScene(renderTexture, renderSurface));

	//テキストビューアで使用するフォントをロード
	FontManager::Instance()->LoadFont("data/FONT/Makinas-4-Square.otf");
	FontManager::Instance()->LoadFont("data/FONT/Text_cinecaption226.ttf");

	//初期シーンに遷移
	const int InitScene = GameConfig::SceneID::Game;
	sceneManager->ChangeScene(InitScene);
}

/**************************************
更新処理
***************************************/
void GameMain::Update()
{
	BaseGame::Update();

	Debug::Begin("Scene");

	if (Debug::Button("Game"))
		sceneManager->ChangeScene(GameConfig::Game);
	else if (Debug::Button("ParticleTest"))
		sceneManager->ChangeScene(GameConfig::ParticleTest);
	else if (Debug::Button("ModelView"))
		sceneManager->ChangeScene(GameConfig::ModelView);
	else if (Debug::Button("Mophing"))
		sceneManager->ChangeScene(GameConfig::MophingTest);

	Debug::End();
}