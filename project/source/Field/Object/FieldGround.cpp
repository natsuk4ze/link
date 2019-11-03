//=====================================
//
//FieldGround.cpp
//機能:フィールド地面
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldGround.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

namespace Field
{
	/**************************************
	コンストラクタ
	***************************************/
	FieldGround::FieldGround()
	{
		ResourceManager::Instance()->MakePolygon("FieldGround", "data/TEXTURE/Field/ground.jpg", { 1000.0f, 1000.0f }, { 500.0f, 500.0f });
		polygon = new BoardPolygon();
		
		ResourceManager::Instance()->GetPolygon("FieldGround", polygon);

		transform->Rotate(90.0f, 0.0f, 0.0f);
	}

	/**************************************
	デストラクタ
	***************************************/
	FieldGround::~FieldGround()
	{
		SAFE_DELETE(polygon);
	}

	/**************************************
	描画処理
	***************************************/
	void FieldGround::Draw()
	{
		polygon->Draw(transform->GetMatrix());
	}
}