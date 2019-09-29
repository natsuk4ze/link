//=====================================
//
//コライダーマネージャ処理[ColliderManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ColliderManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
ボックスコライダー作成処理
***************************************/
std::shared_ptr<BoxCollider3D> ColliderManager::CreateBoxCollider(const std::string & tag, const std::shared_ptr<Transform> transform)
{	
	//コライダーのインスタンス作成
	std::shared_ptr<BoxCollider3D> ptr = std::make_shared<BoxCollider3D>(tag, transform);

	//コンテナにコライダーへのweak_ptrを追加
	boxColliderMap[tag].push_back(std::weak_ptr<BoxCollider3D>(ptr));
	
	return ptr;
}

/**************************************
ボックスコライダー作成処理
***************************************/
std::shared_ptr<BoxCollider3D> ColliderManager::CreateBoxCollider(const std::string & tag, const std::shared_ptr<Transform> transform, const D3DXVECTOR3 & size)
{
	//コライダーのインスタンス作成
	std::shared_ptr<BoxCollider3D> ptr = std::make_shared<BoxCollider3D>(tag, transform, size);

	//コンテナにコライダーへのweak_ptrを追加
	boxColliderMap[tag].push_back(std::weak_ptr<BoxCollider3D>(ptr));

	return ptr;
}

/**************************************
衝突判定処理
***************************************/
void ColliderManager::Update()
{
	//参照不能なポインタを削除
	for (auto&& pair : boxColliderMap)
	{
		pair.second.remove_if([](std::weak_ptr<BoxCollider3D> ptr)
		{
			return ptr.expired();
		});
	}
}

/**************************************
クリア処理
***************************************/
void ColliderManager::Clear()
{
	for (auto&& pair : boxColliderMap)
	{
		pair.second.clear();
	}
	boxColliderMap.clear();
}

/**************************************
指定したタグのコライダー同士で総当たり判定
***************************************/
void ColliderManager::CheckRoundRobin(const std::string & tag1, const std::string & tag2)
{
	//NOTE : この関数の前で参照不能なポインタは削除しているので、寿命・リンク切れは気にしない

	//存在しないタグの場合は早期リターン
	if (boxColliderMap.count(tag1) == 0 || boxColliderMap.count(tag2) == 0)
		return;

	for (auto&& ptr1 : boxColliderMap[tag1])
	{
		//アクティブでないコライダーはcontinue
		std::shared_ptr<BoxCollider3D> collider1 = ptr1.lock();
		if (!collider1->IsActive())
			continue;

		for (auto&& ptr2 : boxColliderMap[tag2])
		{
			//アクティブでないコライダーはcontinue
			std::shared_ptr<BoxCollider3D> collider2 = ptr2.lock();
			if (!collider2->IsActive())
				continue;

			//自分自身との判定は行わない
			if (collider1 == collider2)
				continue;

			//衝突判定
			collider1->CheckCollision(*collider2);
		}
	}
}


