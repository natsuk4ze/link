//=====================================
//
//シーンマネージャ処理[SceneManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "SceneManager.h"
#include "BaseScene.h"
#include "../Resource/ResourceManager.h"
#include "../Tool/ProfilerCPU.h"
#include "../Tween/Tween.h"
#include "../Sound/SoundEffect.h"
#include "../Sound/BackgroundMusic.h"
#include "../Core/ObjectPool.h"

using namespace std;
/**************************************
staticメンバ
***************************************/
SceneManager* SceneManager::mInstance = NULL;

/**************************************
コンストラクタ
***************************************/
SceneManager::SceneManager() :
	current(NULL),
	prev(NULL)
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}
}

/**************************************
デストラクタ
***************************************/
SceneManager::~SceneManager()
{
	Utility::DeleteMap(sceneContainer);

	if (mInstance == this)
	{
		mInstance = NULL;
	}
}

/**************************************
シーンチェンジ処理
***************************************/
void SceneManager::ChangeScene(const int sceneID)
{
	//シーンの存在確認
	if (!mInstance->ExistsScene(sceneID))
	{
		MessageBox(0, "NextScene is Not Found", "Error", 0);
		return;
	}

	//シーン切り替え
	mInstance->_ChengeScene(sceneID);
}

/**************************************
シーンチェンジ処理(内部)
***************************************/
void SceneManager::_ChengeScene(const int sceneID)
{
	//現在のシーンを終了
	if (current != NULL)
	{
		current->Uninit();
		ObjectPool::Instance()->ClearAll();
		ResourceManager::Instance()->AllRelease();
		ProfilerCPU::Instance()->Clear();
		Tween::mInstance->ClearAll();

		//NOTE:重いかも？
		BGM::Clear();
		SE::Clear();
	}

	//切り替え
	prev = current;
	current = sceneContainer[sceneID];

	//初期化
	current->Init();
}

/**************************************
シーン追加処理
***************************************/
void SceneManager::Add(const int sceneID, BaseScene* scene)
{
	if (ExistsScene(sceneID))
		return;

	sceneContainer[sceneID] = scene;
}

/**************************************
更新処理
***************************************/
void SceneManager::Update()
{
	current->Update();
}

/**************************************
描画処理
***************************************/
void SceneManager::Draw()
{
	current->Draw();
}

/**************************************
シーン終了処理
***************************************/
void SceneManager::Uninit()
{
	//現在のシーンを終了
	if (current != NULL)
	{
		current->Uninit();
		ObjectPool::Instance()->ClearAll();
		ResourceManager::Instance()->AllRelease();
		ProfilerCPU::Instance()->Clear();
		Tween::mInstance->ClearAll();

		//NOTE:重いかも？
		BGM::Clear();
		SE::Clear();
	}
}

/**************************************
シーンの存在確認
***************************************/
bool SceneManager::ExistsScene(const int sceneID)
{
	return sceneContainer.count(sceneID) != 0;
}

/**************************************
クリア処理
***************************************/
void SceneManager::Clear()
{
	Utility::DeleteMap(sceneContainer);
}
