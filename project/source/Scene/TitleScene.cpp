//=====================================
//
//TitleScene.cpp
//機能:タイトルシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleScene.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
初期化処理
***************************************/
void TitleScene::Init()
{
	//カメラ作成
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);
}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
}

/**************************************
更新処理
***************************************/
void TitleScene::Update()
{
}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	Debug::Log("CurrentScene:Title");
}
