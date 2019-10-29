//=====================================
//
//AlongActor.cpp
//機能:道沿いのアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AlongActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Tween/Tween.h"

namespace Field::Along
{
	/**************************************
	コンストラクタ
	***************************************/
	AlongActor::AlongActor()
	{
		mesh = new MeshContainer();
		ResourceManager::Instance()->GetMesh("AlongActor", mesh);
	}

	/**************************************
	デストラクタ
	***************************************/
	AlongActor::~AlongActor()
	{
		SAFE_DELETE(mesh);
	}

	/**************************************
	更新処理
	***************************************/
	void AlongActor::Update()
	{
	}

	/**************************************
	描画処理
	***************************************/
	void AlongActor::Draw(const D3DXMATRIX& parent)
	{
		transform->SetWorld(&parent);
		mesh->Draw();
	}

	/**************************************
	アニメーション再生
	***************************************/
	void AlongActor::PlayAnimation()
	{
		Tween::Scale(*this, Vector3::Zero, Vector3::One, 15, InCubic);
	}
}