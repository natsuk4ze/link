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
	current(0),
	nextDest(0),
	callbackToAlong(callback)
{
	this->route = root;

	// あとでフォールドレベルを反映させる
	actor = new PassengerActor(this->route[0], FModel::City);
	D3DXVECTOR3 destination = FindDestination();
	actor->MoveDest(destination, [=]
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
	route.clear();
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
	for (unsigned i = current; i <= nextDest; i++)
	{
		(*callbackToAlong)(route[i]);
	}

	// 目的地に到達しているか確認
	if ((size_t)nextDest >= route.size() - 1)
	{
		actor->SetActive(false);
		return;
	}

	// 次の目的地へセット
	current = nextDest;
	D3DXVECTOR3 destination = FindDestination();
	actor->MoveDest(destination, [=]
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
	this->route = root;

	// あとでフォールドレベルを反映させる
	actor->SetActive(true);
	actor->SetPosition(this->route[0]);
	current = nextDest = 0;
	actor->MoveDest(this->route[nextDest], [=]
	{
		CheckCallback();
	});
}

//=====================================
// アクターの目的地を探す
//=====================================
D3DXVECTOR3 PassengerModel::FindDestination()
{
	D3DXVECTOR3 position = route[current];
	D3DXVECTOR3 offset = route[current + 1] - position;

	unsigned i = current;
	for (; i < route.size() - 1; i++, nextDest++)
	{
		D3DXVECTOR3 next = position + offset * (i + 1 - current);

		//曲がり角に出くわすまで検索する
		if (!Vector3::Equal(next, route[i + 1]))
		{
			return route[i];
		}
	}

	nextDest = route.size() - 1;
	return route.back();
}
