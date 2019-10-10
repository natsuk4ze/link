//=====================================
//
//FieldConfig.h
//機能:フィールド関連の設定値
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCONFIG_H_
#define _FIELDCONFIG_H_

#include "Place\PlaceConfig.h"

#include <vector>
#include <algorithm>

namespace Field
{
	/**************************************
	PlaceModelの座標構造体
	***************************************/
	struct FieldPosition
	{
		int x, z;

		FieldPosition()
		{
			x = 0;
			z = 0;
		}

		FieldPosition(int x, int z)
		{
			this->x = x;
			this->z = z;
		}
	};

	/**************************************
	フィールドの移動可能な境界
	***************************************/
	struct FieldBorder
	{
		int forward;		//Zプラス方向の境界
		int right;			//Xプラス方向の境界
		int back;			//Zマイナス方向の境界
		int left;			//Zマイナス方向の境界

		FieldBorder(int forward, int right, int back, int left) :
			forward(forward), right(right), back(back), left(left)
		{

		}
	};

	/**************************************
	直線方向を表す列挙子
	***************************************/
	enum StraightType
	{
		NotStraight,
		BackAndForward,
		RightAndLeft
	};

	/**************************************
	直線方向の判定処理
	***************************************/
	inline StraightType IsStraight(std::vector<Model::Adjacency>& adjacencyList)
	{
		if (adjacencyList.size() != 2)
			return StraightType::NotStraight;

		auto itrBack = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Back);
		auto itrForward = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Forward);
		if (itrBack != adjacencyList.end() && itrForward != adjacencyList.end())
			return StraightType::BackAndForward;

		auto itrRight = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Right);
		auto itrLeft = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Left);
		if (itrRight != adjacencyList.end() && itrLeft != adjacencyList.end())
			return StraightType::RightAndLeft;

		return StraightType::NotStraight;
	}

	/**************************************
	カーブ方向を表す列挙子
	***************************************/
	enum CurveType
	{
		NotCurve,
		BackAndRight,
		BackAndLeft,
		LeftAndForward,
		ForwardAndRight
	};

	/**************************************
	カーブ方向の判定処理
	***************************************/
	inline CurveType IsCurve(std::vector<Model::Adjacency>& adjacencyList)
	{
		if (adjacencyList.size() != 2)
			return CurveType::NotCurve;

		auto itrBack = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Back);
		auto itrLeft = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Left);

		if (itrBack != adjacencyList.end() && itrLeft != adjacencyList.end())
			return CurveType::BackAndLeft;

		auto itrRight = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Right);
		if (itrBack != adjacencyList.end() && itrRight != adjacencyList.end())
			return CurveType::BackAndRight;

		auto itrForward = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Forward);
		if (itrLeft != adjacencyList.end() && itrForward != adjacencyList.end())
			return CurveType::LeftAndForward;
		else
			return CurveType::ForwardAndRight;

	}

	/**************************************
	十字路の向き列挙子
	***************************************/
	enum TjunctionType
	{
		NotTjunction,
		ExceptBack,
		ExceptLeft,
		ExceptForward,
		ExceptRight
	};

	/**************************************
	十字路の向きの判定処理
	***************************************/
	inline TjunctionType IsTjunction(std::vector<Model::Adjacency>& adjacencyList)
	{
		if (adjacencyList.size() != 3)
			return TjunctionType::NotTjunction;

		auto itr = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Back);
		if (itr == adjacencyList.end())
			return TjunctionType::ExceptBack;

		itr = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Left);
		if (itr == adjacencyList.end())
			return TjunctionType::ExceptLeft;

		itr = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Forward);
		if (itr == adjacencyList.end())
			return TjunctionType::ExceptForward;

		return TjunctionType::ExceptRight;
	}
}

#endif