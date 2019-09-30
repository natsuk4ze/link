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
#include "../../Framework/Renderer3D/SkyBox.h"

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	object = new TransformObject();
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));

	//スカイボックスのテクスチャをロード
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_up.png", SkyBox::Surface::Up);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_back.png", SkyBox::Surface::Back);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_down.jpg", SkyBox::Surface::Down);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_front.png", SkyBox::Surface::Front);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_left.png", SkyBox::Surface::Left);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_right.png", SkyBox::Surface::Right);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(object);
	SAFE_DELETE(skybox);
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
	skybox->Draw();

	object->Draw();
	Debug::Log("CurrentScene:Game");
}
