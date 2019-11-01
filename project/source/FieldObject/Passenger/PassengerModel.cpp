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
PassengerModel::PassengerModel(const std::deque<D3DXVECTOR3>& root, std::function<void(const D3DXVECTOR3&)> *callback) :
	callbackToAlong(callback)
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
	//道沿いのモデルコントローラへアクターが到着した座標を渡す
	//(*callbackToAlong)(root[nextDest]);

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

//=====================================
// 使用中確認
//=====================================
bool PassengerModel::IsActive()
{
	return actor->IsActive();
}

//=====================================
// アクターのセット
//=====================================
void PassengerModel::SetActor(const std::deque<D3DXVECTOR3>& root)
{
	this->root = root;
	// あとでフォールドレベルを反映させる
	actor->SetActive(true);
	actor->SetPosition(this->root[0]);
	nextDest = 1;
	actor->MoveDest(this->root[nextDest], [=]
	{
		CheckCallback();
	});
}