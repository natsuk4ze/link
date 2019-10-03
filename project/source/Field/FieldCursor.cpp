//=====================================
//
//FieldCursor.cpp
//機能:フィールドカーソル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCursor.h"
#include "../../Framework/Math/Easing.h"

#include <algorithm>

namespace Field
{
	/**************************************
	コンストラクタ
	***************************************/
	FieldCursor::FieldCursor() :
		borderX(0.0f), borderZ(0.0f)
	{
		//四角形生成
		squareContainer.resize(SquareMax);
		for (auto&& square : squareContainer)
		{
			square = new FieldCursorSquare();
		}
	}

	/**************************************
	デストラクタ
	***************************************/
	FieldCursor::~FieldCursor()
	{
		Utility::DeleteContainer(squareContainer);
	}

	/**************************************
	更新処理
	***************************************/
	void FieldCursor::Update()
	{
		//30フレームおきに四角形を発生
		if (cntFrame == 0)
		{
			SetSquare();
		}
		cntFrame = Math::WrapAround(0, EmitInterval, ++cntFrame);

		//四角形更新
		for (auto&& square : squareContainer)
		{
			square->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void FieldCursor::Draw()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//自身のワールド変換行列を作成
		D3DXMATRIX mtxWorld = transform->GetMatrix();

		//四角形をソートして描画
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		std::sort(squareContainer.begin(), squareContainer.end(), &FieldCursorSquare::Compare);

		for (auto&& square : squareContainer)
		{
			square->Draw(mtxWorld);
		}

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	/**************************************
	移動処理
	***************************************/
	void FieldCursor::Move(const D3DXVECTOR3& direction)
	{
		D3DXVECTOR3 position = transform->GetPosition();

		//移動範囲に制限をかける
		position.x = Math::Clamp(-borderX, borderX, position.x + direction.x);
		position.z = Math::Clamp(-borderZ, borderZ, position.z + direction.z);

		transform->SetPosition(position);
	}

	/**************************************
	移動範囲設定処理
	***************************************/
	void FieldCursor::SetBorder(float borderX, float borderZ)
	{
		this->borderX = borderX;
		this->borderZ = borderZ;
	}

	/**************************************
	FieldCursorSquareセット処理
	***************************************/
	void FieldCursor::SetSquare()
	{
		auto itr = std::find_if(squareContainer.begin(), squareContainer.end(), [](auto&& square)
		{
			return !square->IsActive();
		});

		if (itr != squareContainer.end())
		{
			(*itr)->Set();
		}
	}

	/**************************************
	FieldCursorSquareコンストラクタ
	***************************************/
	FieldCursorSquare::FieldCursorSquare() :
		cntFrame(FadeDuration)
	{
		transform = new Transform();

		//XZ平面に対して平行になるように回転
		transform->Rotate(90.0f, 0.0f, 0.0f);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Field/CursorSquare.png");

		//サイズ設定
		SetSize(Size);
	}

	/**************************************
	FieldCursorSquareデストラクタ
	***************************************/
	FieldCursorSquare::~FieldCursorSquare()
	{
		SAFE_DELETE(transform);
	}

	/**************************************
	FieldCursorSquare更新処理
	***************************************/
	void FieldCursorSquare::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//上方向に移動
		transform->Move(Vector3::Up * MoveSpeed);

		//マテリアルの透過率を設定
		float t = (float)cntFrame / FadeDuration;
		material.Diffuse.a = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InExpo);
	}

	/**************************************
	FieldCursorSquare描画処理
	***************************************/
	void FieldCursorSquare::Draw(const D3DXMATRIX& parentMtx)
	{
		if (!IsActive())
			return;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//ワールド変換設定
		transform->SetWorld(&parentMtx);

		//描画
		BoardPolygon::Draw();
	}

	/**************************************
	FieldCursorSquareセット処理
	***************************************/
	void FieldCursorSquare::Set()
	{
		cntFrame = 0;
		transform->SetPosition(Vector3::Zero);
	}

	/**************************************
	FieldCursorSquareアクティブ判定
	***************************************/
	bool FieldCursorSquare::IsActive()
	{
		return cntFrame < FadeDuration;
	}

	/**************************************
	FieldCursorSquare比較演算子
	***************************************/
	bool FieldCursorSquare::Compare(const FieldCursorSquare * lhs, const FieldCursorSquare * rhs)
	{
		return lhs->cntFrame < rhs->cntFrame;
	}
}