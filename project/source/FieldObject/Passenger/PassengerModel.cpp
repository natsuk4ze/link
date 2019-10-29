//=====================================
//
// パッセンジャーモデル[PassengerModel.cpp]
// 機能：パッセンジャーのモデルクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PassengerModel.h"

//=====================================
// コンストラクタ
//=====================================
PassengerModel::PassengerModel(const std::vector<D3DXVECTOR3>& root)
{
	this->root = root;
	// あとでフォールドレベルを反映させる
	actor = new PassengerActor(this->root[0], FModel::City);
	nextDest = 1;
	actor->MoveDest(this->root[nextDest], [=]
	{
		CheckCallback();
	});
}

//=====================================
// デストラクタ
//=====================================
PassengerModel::~PassengerModel()
{
	SAFE_DELETE(actor);
	root.clear();
}

//=====================================
// 更新
//=====================================
void PassengerModel::Update()
{
	actor->Update();
}

//=====================================
// 描画
//=====================================
void PassengerModel::Draw()
{
	actor->Draw();
}

//=====================================
// コールバックの確認
//=====================================
void PassengerModel::CheckCallback()
{
	// 目的地に到達しているか確認
	if ((size_t)nextDest >= root.size() - 1)
	{
		actor->SetActive(false);
		return;
	}

	// 次の目的地へセット
	nextDest++;
	actor->MoveDest(root[nextDest], [=]
	{
		CheckCallback();
	});
}