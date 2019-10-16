//=====================================
//
// プレイスアクター[PlaceActor.cpp]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlaceActor.h"
#include "State/CreateActorState.h"
#include "../../../Framework/Tool/DebugWindow.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 PlaceActor::ActorScale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// コンストラクタ
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel) :
	state(NULL), current(), type()
{
	// メッシュコンテナの作成
	mesh = MeshContainer::Create();

	// ステータスセット
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);
}

//=====================================
// デストラクタ
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_RELEASE(mesh);
	state = NULL;
}

//=====================================
// 更新
//=====================================
PlaceActor::State PlaceActor::Update()
{
	State next = Idle;

	// 状態の更新
	if (state != NULL)
	{
		next = state->OnUpdate(*this);
	}

#if _DEBUG
	Debug();
#endif

	return next;
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

void PlaceActor::Debug()
{
	Debug::Begin("PlaceActor", false);
	Debug::Text("State = %d\n", current);
	Debug::End();
}