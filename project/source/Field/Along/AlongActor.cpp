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
#include "../../Field/Object/WaterHeightController.h"

namespace Field::Along
{
	/**************************************
	staticメンバ
	***************************************/
	const float AlongActor::RangePositionOffset = 2.0f;

	const float AlongActor::MinScale = 0.75f;
	const float AlongActor::MaxScale = 1.25f;
	const float AlongActor::MinScaleY = 1.0f;
	const float AlongActor::MaxScaleY = 1.5f;
	const float AlongActor::SpeedRotate = 1.0f;

	const D3DXCOLOR AlongActor::MaterialColor[] = {
		{ 1.0f, 0.4f, 0.4f, 1.0f },
		{ 0.4f, 0.4f, 1.0f, 1.0f },
		{ 1.0f, 0.9f, 0.6f, 1.0f }
	};

	/**************************************
	コンストラクタ
	***************************************/
	AlongActor::AlongActor(FieldLevel level, bool onWater) :
		level(level),
		onWater(onWater)
	{
		mesh = new MeshContainer();
		int colorIndex = Math::RandomRange(0, 3);

		switch (level)
		{
		case FieldLevel::City:
			ResourceManager::Instance()->GetMesh("AlongCity", mesh);
			mesh->SetMaterialColor(MaterialColor[colorIndex], 1);
			break;

		case FieldLevel::World:
			ResourceManager::Instance()->GetMesh("AlongWorld", mesh);
			break;

		case FieldLevel::Space:
			ResourceManager::Instance()->GetMesh("AlongSpace", mesh);
			mesh->SetMaterialColor(MaterialColor[colorIndex], 0);
			break;
		}

		if (level == FieldLevel::City || level == FieldLevel::World)
		{
			int rotation = Math::RandomRange(0, 8);
			transform->Rotate(rotation * 45.0f, Vector3::Up);
		}
		else if (level == FieldLevel::Space)
		{
			const float AngleRange = 20.0f;

			float angleX = Math::RandomRange(-AngleRange, AngleRange);
			transform->Rotate(angleX, Vector3::Right);
			float angleZ = Math::RandomRange(-AngleRange, AngleRange);
			transform->Rotate(angleZ, Vector3::Forward);
		}
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
		if (level == FieldLevel::Space)
		{
			transform->Rotate(SpeedRotate, Vector3::Up);
		}
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
		float scaleY = Math::RandomRange(MinScaleY, MaxScaleY);

		Tween::Scale(*this, Vector3::Zero, { scale, scaleY, scale }, 15, InCubic);
	}

	/**************************************
	座標設定処理
	***************************************/
	void AlongActor::SetPosition(const D3DXVECTOR3 & position)
	{
		D3DXVECTOR3 offset = Vector3::Zero;
		offset.x = Math::RandomRange(-RangePositionOffset, RangePositionOffset);
		offset.z = Math::RandomRange(-RangePositionOffset, RangePositionOffset);

		if (onWater)
		{
			offset.y = -15.0f;
		}

		transform->SetPosition(position + offset);
	}
}