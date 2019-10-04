//=====================================
//
//RouteModel.cpp
//機能:繋がった道を表すモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RouteModel.h"
#include "../Place/FieldPlaceModel.h"
#include "./../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using宣言
	***************************************/
	using cpplinq::last_or_default;

	/**************************************
	static変数
	***************************************/
	unsigned RouteModel::incrementID = 0;

	/**************************************
	コンストラクタ
	***************************************/
	RouteModel::RouteModel() :
		edgeStart(nullptr), edgeEnd(nullptr),
		uniqueID(incrementID++)
	{

	}

	/**************************************
	コンストラクタ
	***************************************/
	RouteModel::RouteModel(const std::vector<PlaceModel*>& placeVector) :
		edgeStart(nullptr), edgeEnd(nullptr),
		uniqueID(incrementID++)
	{
		route.assign(placeVector.begin(), placeVector.end());

		for (auto&& place : route)
		{
			place->BelongRoute(this);
		}
	}

	/**************************************
	デストラクタ
	***************************************/
	RouteModel::~RouteModel()
	{
		//自身に所属しているプレイスの所属を解除
		edgeStart->ExitRoute(this);
		edgeEnd->ExitRoute(this);
		for (auto&& place : route)
		{
			place->ExitRoute(this);
		}

		adjacentRoute.clear();
		route.clear();
	}

	/**************************************
	更新処理
	***************************************/
	void RouteModel::Update()
	{
		//使用されていないルートモデルを隣接リストから削除
		auto itr = std::remove_if(adjacentRoute.begin(), adjacentRoute.end(), [](AdjacentRoute& adjacaency)
		{
			return adjacaency.route.expired();
		});
		adjacentRoute.erase(itr, adjacentRoute.end());
	}

	/**************************************
	道となるプレイス追加
	***************************************/
	void RouteModel::AddRoad(PlaceModel * place)
	{
		edgeEnd = place;
		route.push_back(place);
		place->BelongRoute(this);
	}

	/**************************************
	隣接ルート追加
	***************************************/
	void RouteModel::AddAdjacency(PlaceModel * junction, PlaceModel * connectTarget, std::shared_ptr<RouteModel> opponent)
	{
		adjacentRoute.push_back(AdjacentRoute(junction, connectTarget, opponent));
	}

	/**************************************
	隣接ルート追加
	***************************************/
	void RouteModel::AddAdjacency(const std::vector<AdjacentRoute>& adjacenctRoute)
	{
		std::copy(adjacenctRoute.begin(), adjacenctRoute.end(), std::back_inserter(this->adjacentRoute));
	}

	/**************************************
	端点設定
	***************************************/
	void RouteModel::SetEdge(PlaceModel * edge)
	{
		if (edgeStart == nullptr)
			edgeStart = edge;
		else
			edgeEnd = edge;

		edge->BelongRoute(this);
	}

	/**************************************
	端点設定
	***************************************/
	void RouteModel::SetEdge()
	{
		//始点から端点を設定
		PlaceModel* first = *route.begin();
		_SetEdge(first);

		//終点から端点を設定
		PlaceModel* last = *route.rbegin();
		_SetEdge(last);
	}

	/**************************************
	端点取得
	***************************************/
	PlaceModel * RouteModel::GetEdge(Edge type)
	{
		if (type == Edge::Start)
			return edgeStart;
		else
			return edgeEnd;
	}

	/**************************************
	他方の端点取得
	***************************************/
	PlaceModel * RouteModel::GetOtherEdge(PlaceModel * edge)
	{
		if (edgeStart == edge)
			return edgeEnd;
		else
			return edgeStart;
	}

	/**************************************
	繋がっている街を取得
	***************************************/
	PlaceModel * RouteModel::GetConnectedTown(PlaceModel * self)
	{
		if (edgeStart->IsType(PlaceType::Town) && edgeStart != self)
			return edgeStart;
		
		if (edgeEnd->IsType(PlaceType::Town) && edgeEnd != self)
			return edgeEnd;

		return nullptr;
	}

	/**************************************
	ルート取得（端点は含まない）
	***************************************/
	std::vector<PlaceModel*> RouteModel::GetRoute()
	{
		return route;
	}

	/**************************************
	隣接ルート取得
	***************************************/
	std::vector<AdjacentRoute> RouteModel::GetAdjacencies()
	{
		return adjacentRoute;
	}

	/**************************************
	端点設定（内部処理）
	***************************************/
	void RouteModel::_SetEdge(PlaceModel* place)
	{
		//連結相手を取得
		PlaceModel* opponent = place->GetEdgeOpponent();
		SetEdge(opponent);
		opponent->BelongRoute(this);

		//TODO:街なら出口を増やす
	}
}