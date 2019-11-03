//=====================================
//
//ユーティリティヘッダ[Utility.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <algorithm>
#include "../../Library/nameof/nameof.hpp"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
namespace Utility
{
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

	/**************************************
	コンテナ内検索処理
	***************************************/
	template<class T, class OBJ>
	static inline bool IsContain(T& container, const OBJ& target)
	{
		auto itr = std::find(container.begin(), container.end(), target);

		return itr != container.end();
	}

	/**************************************
	enumの文字列化
	***************************************/
	template <class Enum>
	std::string ToString(const Enum& val)
	{
		return std::string(NAMEOF_ENUM(val));
	}
};

#endif