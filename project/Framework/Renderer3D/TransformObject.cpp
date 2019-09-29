//=====================================
//
//トランスフォームオブジェクト処理[TransformObject.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TransformObject.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
TransformObject::TransformObject()
{
	mesh = MeshContainer::Create();
	mesh->Load("data/MODEL/transform.x");
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