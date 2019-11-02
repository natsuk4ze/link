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
	staticメンバ
	***************************************/
	const float AlongActor::RangePositionOffset = 1.5f;
	const float AlongActor::MinScale = 0.9f;
	const float AlongActor::MaxScale = 1.2f;

	/**************************************
	コンストラクタ
	***************************************/
	AlongActor::AlongActor()
	{
		mesh = new MeshContainer();
		ResourceManager::Instance()->GetMesh("AlongCity", mesh);
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
		float scale = Math::RandomRange(MinScale, MaxScale);
		Tween::Scale(*this, Vector3::Zero, Vector3::One * scale, 15, InCubic);
	}

	/**************************************
	座標設定処理
	***************************************/
	void AlongActor::SetPosition(const D3DXVECTOR3 & position)
	{
		float offsetX = Math::RandomRange(-RangePositionOffset, RangePositionOffset);
		float offsetY = Math::RandomRange(-RangePositionOffset, RangePositionOffset);
		float offsetZ = Math::RandomRange(-RangePositionOffset, RangePositionOffset);

		transform->SetPosition(position + D3DXVECTOR3(offsetX, offsetY, offsetZ));
	}
}