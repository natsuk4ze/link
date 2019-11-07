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
PassengerModel::PassengerModel(const std::deque<D3DXVECTOR3>& root, Field::FieldLevel level, std::function<void(const D3DXVECTOR3&)> *callback) :
	current(0),
	nextDest(0),
	callbackToAlong(callback)
{
	this->route = root;

	actor = new PassengerActor(this->route[0], level);
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
	for (int i = current; i <= nextDest; i++)
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
void PassengerModel::SetActor(const std::deque<D3DXVECTOR3>& root, Field::FieldLevel level)
{
	this->route = root;

	switch (level)
	{
	case Field::City:
		if (actor->GetType() != PassengerActor::Car)
		{
			ChangeMesh("Car");
		}
		break;
	case Field::World:
		if (actor->GetType() != PassengerActor::Train)
		{
			ChangeMesh("Train");
		}
		break;
	case Field::Space:
		if (actor->GetType() != PassengerActor::SpaceShip)
		{
			ChangeMesh("SpaceShip");
		}
		break;
	default:
		break;
	}

	// あとでフィールドレベルを反映させる
	actor->SetActive(true);
	actor->SetPosition(this->route[0]);
	this->current = nextDest = 0;
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
		D3DXVECTOR3 next = position + offset * (i + 1.0f - current);

		//曲がり角に出くわすまで検索する
		if (!Vector3::Equal(next, route[i + 1]))
		{
			return route[i];
		}
	}

	nextDest = route.size() - 1;
	return route.back();
}

//=====================================
// アクターの座標をフィールド座標に変換して返す
//=====================================
Field::FieldPosition PassengerModel::GetFieldPosition()
{
	return Field::FieldPosition::ConvertToFieldPosition(actor->GetPosition());
}

//=====================================
// アクターのメッシュ変更
//=====================================
void PassengerModel::ChangeMesh(const char* tag)
{
	actor->ChangeMesh(tag);
}

//=====================================
// アクターの現在のメッシュの状態を取得
//=====================================
PassengerActor::State PassengerModel::GetType()
{
	return actor->GetType();
}

//=====================================
// アクターのタグを変更
//=====================================
void PassengerModel::SetType(PassengerActor::State next)
{
	actor->SetType(next);
}