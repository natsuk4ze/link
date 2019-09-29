//=====================================
//
//GameScene.cpp
//機能:ゲームシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../../Framework/Renderer3D/TransformObject.h"

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	object = new TransformObject();

	//カメラの位置を初期化

}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(object);
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{

}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	object->Draw();
	Debug::Log("CurrentScene:Game");
}
