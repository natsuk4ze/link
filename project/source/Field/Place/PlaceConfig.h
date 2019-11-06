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
#include <memory>
#include "../../../Framework/Math/TMath.h"

/**************************************
マクロ定義
***************************************/
#define DEBUG_PLACEMODEL

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class RouteModel;
	class PlaceModel;

	/**************************************
	using宣言
	***************************************/
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
	隣接方向の逆側を求める処理
	***************************************/
	inline Adjacency GetInverseSide(const Adjacency adjacency)
	{
		if (adjacency >= Adjacency::Max)
			return NotAdjacenct;
		else
			return (Adjacency)Math::WrapAround(Adjacency::Back, Adjacency::Max, adjacency + 2);

	}

	// 各PlaceActorごとのデータを取得するための構造体
	struct PlaceData
	{
		Field::FieldPosition key;
		int townLevel;
	};

}
#endif