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

static float t = 0.0f;
static int cntFrame = 0;

/**************************************
初期化処理
***************************************/
void MophingTestScene::Init()
{
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	skybox = new Field::FieldSkyBox(Field::FieldLevel::World);
	morphContainer = new MorphingMeshContainer();
	stoneMesh = new MorphingMeshContainer();

	ResourceManager::Instance()->LoadMesh("town", "data/MODEL/Mophing/town.x");
	ResourceManager::Instance()->LoadMesh("town2", "data/MODEL/Mophing/town_m.x");
	ResourceManager::Instance()->LoadMesh("ishi", "data/MODEL/Mophing/ishi.x");
	ResourceManager::Instance()->LoadMesh("ishi2", "data/MODEL/Mophing/ishi2.x");

	ResourceManager::Instance()->GetMesh("town", morphContainer);
	morphContainer->RegisterVertex(0);

	ResourceManager::Instance()->GetMesh("town2", morphContainer);
	morphContainer->RegisterVertex(1);

	ResourceManager::Instance()->GetMesh("ishi", stoneMesh);
	stoneMesh->RegisterVertex(0);

	ResourceManager::Instance()->GetMesh("ishi2", stoneMesh);
	stoneMesh->RegisterVertex(1);

	morphContainer->SetCurrent(0);
	morphContainer->SetNext(1);

	stoneMesh->SetNext(1);
}

/**************************************
終了処理
***************************************/
void MophingTestScene::Uninit()
{
	SAFE_RELEASE(vtx1);
	SAFE_RELEASE(vtx2);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(texture);
	SAFE_RELEASE(declare);

	attributeTable.clear();
	materials.clear();
	materialNum = 0;

	SAFE_DELETE(effect);

	SAFE_DELETE(sceneCamera);

	SAFE_DELETE(morphContainer);
	SAFE_DELETE(stoneMesh);
}

/**************************************
更新処理
***************************************/
void MophingTestScene::Update()
{
	Debug::Begin("Mophing");
	static int period = 30;

	Debug::Slider("period", period, 10, 120);

	float time = (float)cntFrame++ / period;
	t = Easing::EaseValue(time, 1.0f, 0.0f, EaseType::InOutExpo);

	cntFrame = Math::WrapAround(0, period, cntFrame);
	Debug::End();

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
	//static float t = 0.0f;

	Debug::Begin("Mophing");
	Debug::Slider("pos", pos, Vector3::One * -1000.0f, Vector3::One * 1000.0f);
	Debug::Slider("scl", scale, Vector3::Zero, Vector3::One * 20.0f);
	Debug::Slider("rot", rot, Vector3::Zero, Vector3::One * 360.0f);
	//Debug::Slider("t", t, 0.0f, 1.0f);
	Debug::End();

	transform.SetPosition(pos);
	transform.SetScale(scale);
	transform.SetRotation(rot);

	morphContainer->SetChange(t);
	morphContainer->Draw(transform.GetMatrix());

	transform.SetPosition({ 150.0f, 25.0f, 1000.0f });

	stoneMesh->SetChange(t);
	stoneMesh->Draw(transform.GetMatrix());
}
