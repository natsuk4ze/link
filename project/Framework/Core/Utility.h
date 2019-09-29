//=====================================
//
//ユーティリティヘッダ[Utility.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class Utility
{
public:
	/**************************************
	クラス定義
	***************************************/
	template <class T>
	static void DeleteContainer(T& container)
	{
		for (auto&& p : container)
		{
			delete p;
			p = NULL;
		}
		container.clear();
	}

	/**************************************
	クラス定義
	***************************************/
	template <class T>
	static void DeleteMap(T& map)
	{
		for (auto&& pair : map)
		{
			delete pair.second;
			pair.second = NULL;
		}
		map.clear();
	}

private:
	Utility();
};

#endif