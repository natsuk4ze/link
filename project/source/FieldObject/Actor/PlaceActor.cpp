//=====================================
//
// プレイスアクター[PlaceActor.cpp]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlaceActor.h"
#include "State/CreateActorState.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 PlaceActor::ActorScale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// コンストラクタ
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
{
	// メッシュコンテナの作成
	mesh = MeshContainer::Create();

	// ステータスセット
	transform->SetPosition(pos);
	transform->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	this->SetActive(true);

	// state = NULL;

	state = new CreateActorState();
	state->OnStart(*this);
}

//=====================================
// デストラクタ
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// 更新
//=====================================
PlaceActor::State PlaceActor::Update()
{
	// 状態の更新
	return state->OnUpdate(*this);

}

//=====================================
// 描画
//=====================================
void PlaceActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y軸回転
//=====================================
void PlaceActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// ステートの切り替え
//=====================================
void PlaceActor::ChangeState(ActorState *next)
{
	state = next;
	state->OnStart(*this);
}

//=====================================
// メッシュデータのカラー変更
//=====================================
void PlaceActor::SetColor(const D3DXCOLOR& color, UINT index)
{
	mesh->SetMaterialColor(color, index);
}