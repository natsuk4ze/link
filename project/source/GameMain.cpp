//=====================================
//
//GameMain.cpp
//機能:ゲームメイン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameMain.h"
#include "../Framework/Core/SceneManager.h"
#include "GameConfig.h"

#include "Scene\GameScene.h"
#include "Scene/ParticleTestScene.h"

/**************************************
コンストラクタ
***************************************/
GameMain::GameMain(HINSTANCE hInstance, HWND hWnd) :
	BaseGame(hInstance, hWnd)
{
	//シーンマネージャにシーンのインスタンスを追加
	sceneManager->Add(GameConfig::SceneID::Game, new GameScene());
	sceneManager->Add(GameConfig::SceneID::ParticleTest, new ParticleTestScene());

	//初期シーンに遷移
	const int InitScene = GameConfig::SceneID::ParticleTest;
	sceneManager->ChangeScene(InitScene);
}