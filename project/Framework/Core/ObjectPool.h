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

#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <string>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class ObjectPool : public BaseSingleton<ObjectPool>
{
	friend class SceneManager;
public:
	/**************************************
	コンストラクタ
	***************************************/
	ObjectPool()
	{

	}

	/**************************************
	デストラクタ
	***************************************/
	~ObjectPool()
	{
		ClearAll();
	}

	/**************************************
	オブジェクトインスタンス作成処理
	生ポインタを返すので、削除について必ず管理すること
	***************************************/
	template<class T, class ...TArgs>
	T* Create(TArgs... args)
	{
		std::string key = typeid(T).name();
		std::vector<GameObject*>* container = &objectPool[key];

		T* ptr = nullptr;
		
		if (container->empty())
		{
			ptr = new T();
		}
		else
		{
			ptr = dynamic_cast<T*>(container->back());
			container->pop_back();
		}

		ptr->Init(args...);

		return ptr;
	}

	/**************************************
	オブジェクトインスタンス削除処理
	※実際には削除せずプールしておき、シーン遷移時に削除
	***************************************/
	template<class T>
	void Destroy(T* object)
	{
		if (object == nullptr)
			return;

		object->Uninit();

		std::string key = typeid(*object).name();
		objectPool[key].push_back(object);

		object = nullptr;

		return;
	}

private:
	std::unordered_map<std::string, std::vector<GameObject*>> objectPool;

	/**************************************
	オブジェクトインスタンス解放処理
	***************************************/
	void ClearAll()
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
};
#endif