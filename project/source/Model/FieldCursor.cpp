//=====================================
//
//FieldCursor.cpp
//機能:フィールドカーソル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCursor.h"
#include <algorithm>

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
	Math::WrapAround(0, EmitInterval, ++cntFrame);

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
	//自身のワールド変換行列を作成
	D3DXMATRIX mtxWorld = transform->GetMatrix();

	//四角形を描画
	for (auto&& square : squareContainer)
	{
		square->Draw(mtxWorld);
	}
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
	//非アクティブなスクエアを探してセット
	auto itr = std::find_if(squareContainer.begin(), squareContainer.end(), [](auto square)
	{
		return !square->IsActive();
	});

	(*itr)->Set();
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
	material.Diffuse.a = 1.0f * cntFrame / FadeDuration;
}

/**************************************
FieldCursorSquare描画処理
***************************************/
void FieldCursorSquare::Draw(const D3DXMATRIX& parentMtx)
{
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
}

/**************************************
FieldCursorSquareアクティブ判定
***************************************/
bool FieldCursorSquare::IsActive()
{
	return cntFrame < FadeDuration;
}
