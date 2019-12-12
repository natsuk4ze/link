//=====================================
//
//MophingTestScene.cpp
//機能:モーフィングテストシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MophingTestScene.h"
#include "../../Framework/Effect/MophingEffect.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Renderer3D/MophingMeshContainer.h"
#include "../../Framework/Math/Easing.h"

#include "../Field/Object/FieldSkyBox.h"

/**************************************
初期化処理
***************************************/
void MophingTestScene::Init()
{
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	skybox = new Field::FieldSkyBox(Field::FieldLevel::World);
	morphContainer = new MorphingMeshContainer();
	mesh = new MeshContainer();

	ResourceManager::Instance()->LoadMesh("town", "data/MODEL/Mophing/town.x");
	ResourceManager::Instance()->LoadMesh("town2", "data/MODEL/Mophing/town_m.x");
	ResourceManager::Instance()->LoadMesh("town3", "data/MODEL/Mophing/town_last.x");

	ResourceManager::Instance()->GetMesh("town", morphContainer);
	morphContainer->RegisterVertex(0);

	ResourceManager::Instance()->GetMesh("town2", morphContainer);
	morphContainer->RegisterVertex(1);

	ResourceManager::Instance()->GetMesh("town3", morphContainer);
	morphContainer->RegisterVertex(2);

	morphContainer->SetCurrent(0);
	morphContainer->SetNext(1);

	ResourceManager::Instance()->GetMesh("town", mesh);
}

/**************************************
終了処理
***************************************/
void MophingTestScene::Uninit()
{
	SAFE_DELETE(sceneCamera);

	SAFE_DELETE(morphContainer);

	SAFE_DELETE(mesh);
}

/**************************************
更新処理
***************************************/
void MophingTestScene::Update()
{
	sceneCamera->Update();
}

/**************************************
描画処理
***************************************/
void MophingTestScene::Draw()
{
	sceneCamera->Set();

	skybox->Draw();
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	static Transform transform;
	static D3DXVECTOR3 pos = Vector3::Forward * 200.0f, scale = Vector3::One, rot = Vector3::Zero;
	static float t = 0.0f;

	Debug::Begin("Mophing");
	Debug::Slider("pos", pos, Vector3::One * -1000.0f, Vector3::One * 1000.0f);
	Debug::Slider("scl", scale, Vector3::Zero, Vector3::One * 20.0f);
	Debug::Slider("rot", rot, Vector3::Zero, Vector3::One * 360.0f);
	if (Debug::Slider("t", t, 0.0f, 2.0f))
	{
		if (t < 1.0f)
		{
			morphContainer->SetCurrent(0);
			morphContainer->SetNext(1);
			morphContainer->SetChange(t);
		}
		else
		{
			morphContainer->SetCurrent(1);
			morphContainer->SetNext(2);
			morphContainer->SetChange(t - 1.0f);
		}

	};
	Debug::End();

	transform.SetPosition(pos);
	transform.SetScale(scale);
	transform.SetRotation(rot);

	morphContainer->Draw(transform.GetMatrix());

	transform.Move(Vector3::Right * 150.0f);

	transform.SetWorld();
	mesh->Draw();
}
