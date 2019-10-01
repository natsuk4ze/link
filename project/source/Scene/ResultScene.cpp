//=====================================
//
//ResultScene.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResultScene.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
初期化処理
***************************************/
void ResultScene::Init()
{
	//カメラ作成
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);
}

/**************************************
終了処理
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
}

/**************************************
更新処理
***************************************/
void ResultScene::Update()
{
}

/**************************************
描画処理
***************************************/
void ResultScene::Draw()
{
	Debug::Log("CurrenstScene:Result");
}
