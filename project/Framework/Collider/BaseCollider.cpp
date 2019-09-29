//=====================================
//
//コライダーオブザーバー処理[ColliderObserver.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ColliderObserver.h"
#include "BaseCollider.h"

#include <algorithm>

/**************************************
コンストラクタ
***************************************/
BaseCollider::BaseCollider(const std::shared_ptr<Transform> transform) :
	active(true)
{
	refTransform = transform;
}

/**************************************
デストラクタ
***************************************/
BaseCollider::~BaseCollider()
{
	refTransform.reset();
}

/**************************************
アクティブセット処理
***************************************/
void BaseCollider::SetActive(bool state)
{
	active = state;
}

/**************************************
アクティブ判定
***************************************/
bool BaseCollider::IsActive()
{
	return active;
}

/**************************************
オブザーバー追加処理
***************************************/
void BaseCollider::AddObserver(ColliderObserver * observer)
{
	//重複確認
	auto itr = std::find(observers.begin(), observers.end(), observer);

	if (itr != observers.end())
		return;

	observers.push_back(observer);
}

/**************************************
オブザーバー削除処理
***************************************/
void BaseCollider::RemoveObserver(ColliderObserver * observer)
{
	//登録確認
	auto itr = std::find(observers.begin(), observers.end(), observer);

	if (itr == observers.end())
		return;

	auto newEnd = std::remove(observers.begin(), observers.end(), observer);
	observers.erase(newEnd, observers.end());
}
