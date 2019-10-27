//=====================================
//
// フィールドインフォアクター[FieldInfoActor.cpp]
// 機能：フィールド上の情報を表示するアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "FieldInfoActor.h"
#include "CreateFieldInfoState.h"
#include "IdleFieldInfoState.h"
#include "RemoveFieldInfoState.h"
#include "ConnectFieldInfoState.h"
#include "LinkFieldInfoState.h"
#include "CongestionFieldInfoState.h"

#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 FieldInfoActor::ActorScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
const D3DXVECTOR2 FieldInfoActor::ActorSize = D3DXVECTOR2(2.0f, 2.0f);

//=====================================
// コンストラクタ
//=====================================
FieldInfoActor::FieldInfoActor(const D3DXVECTOR3& pos, State state)
{
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);

	// ビルボード作成
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("Info", polygon);

	// ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Idle] = new IdleFieldInfoState();
	fsm[State::Create] = new CreateFieldInfoState();
	fsm[State::Remove] = new RemoveFieldInfoState();
	fsm[State::Connect] = new ConnectFieldInfoState();
	fsm[State::Link] = new LinkFieldInfoState();
	fsm[State::Congestion] = new CongestionFieldInfoState();

	// ステート初期化
	this->ChangeState(state);
}

//=====================================
// デストラクタ
//=====================================
FieldInfoActor::~FieldInfoActor()
{
	SAFE_DELETE(polygon);

	// ステートマシン削除
	Utility::DeleteContainer(fsm);
}

//=====================================
// 初期化処理
//=====================================
void FieldInfoActor::Init()
{
	ResourceManager::Instance()->MakePolygon("Info", "data/TEXTURE/Info/Info.png", ActorSize);
}

//=====================================
// 更新
//=====================================
void FieldInfoActor::Update()
{
	if (!this->IsActive())
		return;;

	// 現在のステート更新
	State next = infoState->OnUpdate(*this);
	if (next != current)
	{
		ChangeState(next);
	}
}

//=====================================
// 描画
//=====================================
void FieldInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	polygon->Draw();

}

//=====================================
// ステートマシンの切り替え
//=====================================
void FieldInfoActor::ChangeState(State next)
{
	if (fsm[next] == NULL)
		return;

	current = next;
	infoState = fsm[next];
	infoState->OnStart(*this);
}