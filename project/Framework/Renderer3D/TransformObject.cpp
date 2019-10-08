//=====================================
//
//トランスフォームオブジェクト処理[TransformObject.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TransformObject.h"
#include "../Resource/ResourceManager.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
TransformObject::TransformObject()
{
	ResourceManager::Instance()->LoadMesh("Transform", "data/MODEL/transform.x");
	
	mesh = MeshContainer::Create();
	ResourceManager::Instance()->GetMesh("Transform", mesh);
}

/**************************************
デストラクタ
***************************************/
TransformObject::~TransformObject()
{
	SAFE_RELEASE(mesh);
}

/**************************************
描画処理
***************************************/
void TransformObject::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}