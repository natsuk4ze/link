//=====================================
//
//ObjectPool.h
//機能:オブジェクトプール
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _OBJECTPOOL_H_
#define _OBJECTPOOL_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"

#include <typeindex>
#include <unordered_map>
#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class ObjectPool : public BaseSingleton<ObjectPool>
{
public:
	ObjectPool()
	{

	}

	~ObjectPool()
	{
		for (auto&& pair : objectPool)
		{
			for (auto&& object : pair.second)
			{
				SAFE_DELETE(object);
			}
			pair.second.clear();
		}

		objectPool.clear();
	}

	template<class T>
	T* Create()
	{
		std::type_index index = std::type_index(typeid(T));
		std::vector<GameObject*>* container = &objectPool[index];

		if (container->empty())
			return new T;

		T* ptr = container->back();
		container->pop_back();

		return ptr;
	}

	template<class T>
	void Destroy(T* object)
	{
		if (object == nullptr)
			return;

		std::type_index index = std::type_index(typeid(T));
		objectPool[index].push_back(object);

		object = nullptr;

		return;
	}

private:
	std::unordered_map<std::type_index, std::vector<GameObject*>> objectPool;
};
#endif