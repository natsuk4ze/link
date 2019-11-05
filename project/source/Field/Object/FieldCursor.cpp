//=====================================
//
//FieldCursor.cpp
//機能:フィールドカーソル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCursor.h"
#include "../../../Framework/Math/Easing.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Resource/ResourceManager.h"

#include <algorithm>

namespace Field
{
	/**************************************
	static変数
	***************************************/
	const D3DXVECTOR2 FieldCursorSquare::Size = { 6.5f, 6.5f };
	const int FieldCursorSquare::FadeDuration = 40;
	const float FieldCursorSquare::MoveSpeed = 0.45f;

	/**************************************
	コンストラクタ
	***************************************/
	FieldCursor::FieldCursor(float positionOffset) :
		PositionOffset(positionOffset),
		fieldBorder(0, 0, 0, 0),
		position(0, 0),
		cntMove(MoveDuration),
		currentMode(Mode::BuildRoad)
	{
		//リソース作成
		ResourceManager::Instance()->MakePolygon("CursorSquare", "data/TEXTURE/Field/CursorSquare.png", FieldCursorSquare::Size, { 2.0f, 1.0f });

		//四角形生成
		squareContainer.resize(SquareMax);
		for (auto&& square : squareContainer)
		{
			square = new FieldCursorSquare();
			ResourceManager::Instance()->GetPolygon("CursorSquare", square);
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
		//移動
		Move();

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
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		std::sort(squareContainer.begin(), squareContainer.end(), &FieldCursorSquare::Compare);

		for (auto&& square : squareContainer)
		{
			square->SetTextureIndex(currentMode);
			square->Draw(mtxWorld);
		}

		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	/**************************************
	移動処理
	***************************************/
	void FieldCursor::Move(int x, int z)
	{
		if (x == 0 && z == 0)
			return;

		if (cntMove < MoveDuration)
			return;

		//移動開始地点を保存
		startPos = position.ConvertToWorldPosition();

		//X軸の移動を優先して使用(Clampで移動範囲を制限)
		if (x != 0)
			position.x = Math::Clamp(fieldBorder.left,  fieldBorder.right, position.x + x);
		else
			position.z = Math::Clamp(fieldBorder.back, fieldBorder.forward, position.z + z);

		//移動先座標を計算
		moveTarget = position.ConvertToWorldPosition();

		//カウントリセット
		cntMove = 0;
	}

	/**************************************
	座標設定
	***************************************/
	void FieldCursor::SetModelPosition(int x, int z)
	{
		position.x = x;
		position.z = z;

		SetPosition(position.ConvertToWorldPosition());
	}

	/**************************************
	モード切り替え処理
	***************************************/
	void Field::FieldCursor::SetMode(Mode mode)
	{
		currentMode = mode;
	}

	/**************************************
	移動中かどうか
	***************************************/
	bool Field::FieldCursor::IsMoving() const
	{
		return cntMove <= MoveDuration;
	}

	/**************************************
	移動範囲設定処理
	***************************************/
	void FieldCursor::SetBorder(int forward, int right, int back, int left)
	{
		fieldBorder = FieldBorder(forward, right, back, left);
	}

	/**************************************
	座標取得処理
	***************************************/
	FieldPosition FieldCursor::GetModelPosition() const
	{
		return position;
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
	FieldCursor移動処理
	***************************************/
	void FieldCursor::Move()
	{
		cntMove++;

		if (cntMove > MoveDuration)
			return;

		float t = 1.0f * cntMove / MoveDuration;
		D3DXVECTOR3 position = Easing::EaseValue(t, startPos, moveTarget, EaseType::Linear);
		transform->SetPosition(position);
	}

	/**************************************
	FieldCursorSquareコンストラクタ
	***************************************/
	FieldCursorSquare::FieldCursorSquare() :
		cntFrame(FadeDuration)
	{
		transform = new Transform();

		//テクスチャはX方向に2分割
		SetTexDiv({ 2.0f, 1.0f });

		//XZ平面に対して平行になるように回転
		transform->Rotate(90.0f, 0.0f, 0.0f);
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
		float alpha = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InExpo);
		SetDiffuse({ 1.0f, 1.0f, 1.0f, alpha });
	}

	/**************************************
	FieldCursorSquare描画処理
	***************************************/
	void FieldCursorSquare::Draw(const D3DXMATRIX& parentMtx)
	{
		if (!IsActive())
			return;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//ワールド変換行列を計算
		D3DXMATRIX world = transform->GetMatrix();
		D3DXMatrixMultiply(&world, &world, &parentMtx);

		//描画
		BoardPolygon::Draw(world);
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