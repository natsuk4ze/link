//=====================================
//
//PlaceConfig.h
//機能:プレイス設定
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLACECONFIG_H_
#define _PLACECONFIG_H_

#include <vector>
#include <algorithm>

namespace Field::Model
{
	/**************************************
	型エイリアス
	***************************************/
	class RouteModel;
	class PlaceModel;

	using RouteModelPtr = std::shared_ptr<RouteModel>;
	using RouteContainer = std::vector<std::shared_ptr<RouteModel>>;

	/**************************************
	PlaceModelのタイプを表す列挙子
	***************************************/
	enum PlaceType
	{
		None,			//初期状態
		Road,			//道
		Town,			//街
		River,			//川
		Bridge,			//橋
		Junction,		//交差点
		Mountain		//山
	};

	/**************************************
	フィールドレベルのタイプを表す列挙子
	***************************************/
	enum FieldLevel
	{
		City,	// 都市レベル
		World,	// 国レベル
		Space,	// 星レベル
	};

	/**************************************
	CSVのデータをPlaceTypeへ変換する関数
	***************************************/
	inline PlaceType IntToPlaceType(int n)
	{
		if (n == 0)
			return PlaceType::Town;

		if (n == 2)
			return PlaceType::River;

		if (n == 3)
			return PlaceType::Mountain;

		return PlaceType::None;
	}

	/**************************************
	隣接方向を表す列挙子
	***************************************/
	enum Adjacency
	{
		Back,			//Zマイナス方向の隣接
		Left,			//Xマイナス方向の隣接
		Forward,		//Zプラス方向の隣接
		Right,			//Xプラス方向の隣接
		Max,
		NotAdjacenct	//隣接していない
	};

	/**************************************
	Adjacency列挙子の後置インクリメント
	***************************************/
	inline Adjacency operator++(Adjacency& adjacency, int)
	{
		return (adjacency == Adjacency::Max) ? adjacency : Adjacency(adjacency + 1);
	}

	/**************************************
	隣接方向の逆側を求める処理
	***************************************/
	inline Adjacency GetInverseSide(const Adjacency adjacency)
	{
		if (adjacency >= Adjacency::Max)
			return NotAdjacenct;
		else
			return (Adjacency)Math::WrapAround(Adjacency::Back, Adjacency::Max, adjacency + 2);

	}
}
#endif