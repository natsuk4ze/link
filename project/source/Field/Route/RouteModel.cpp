//=====================================
//
//RouteModel.cpp
//機能:繋がった道を表すモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RouteModel.h"
#include "../Place/FieldPlaceModel.h"
#include "../../../Library/cppLinq/cpplinq.hpp"
#include "../../../Framework/Pattern/Delegate.h"
#include "../Place/FieldTownModel.h"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using宣言
	***************************************/
	using cpplinq::last_or_default;
	using cpplinq::from;
	using cpplinq::contains;

	/**************************************
	static変数
	***************************************/
	unsigned RouteModel::incrementID = 0;

	/**************************************
	コンストラクタ
	***************************************/
	RouteModel::RouteModel(DelegatePlace *onConnectTown, DelegatePlace *onCreateJunction) :
		edgeStart(nullptr), edgeEnd(nullptr),
		uniqueID(incrementID++),
		isUnused(false),
		onConnectedTown(onConnectTown),
		onCreateJunction(onCreateJunction)
	{

	}

	/**************************************
	等地比較演算子
	***************************************/
	bool RouteModel::operator==(const RouteModel & rhs) const
	{
		return route == rhs.route;
	}

	/**************************************
	スマートポインタ作成処理
	***************************************/
	RouteModelPtr RouteModel::Create(DelegatePlace *onConnectTown, DelegatePlace *onCreateJunction)
	{
		RouteModelPtr ptr = std::make_shared<RouteModel>(onConnectTown, onCreateJunction);
		return ptr;
	}

	/**************************************
	スマートポインタ作成処理
	***************************************/
	RouteModelPtr RouteModel::Create(DelegatePlace *onConnectTown, DelegatePlace *onCreateJunction, const std::vector<PlaceModel*>& placeVector)
	{
		RouteModelPtr ptr = std::make_shared<RouteModel>(onConnectTown, onCreateJunction);

		ptr->route.assign(placeVector.begin(), placeVector.end());

		for (auto&& place : ptr->route)
		{
			place->BelongRoute(ptr);
		}

		return ptr;
	}

	/**************************************
	デストラクタ
	***************************************/
	RouteModel::~RouteModel()
	{
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
		place->BelongRoute(shared_from_this());
	}

	/**************************************
	プレイスの所属解除
	***************************************/
	void RouteModel::BreakAway()
	{
		//自身に所属しているプレイスの所属を解除
		edgeStart->ExitRoute(shared_from_this());
		edgeEnd->ExitRoute(shared_from_this());
		for (auto&& place : route)
		{
			place->ExitRoute(shared_from_this());
		}
	}

	/**************************************
	隣接ルート追加
	***************************************/
	void RouteModel::AddAdjacency(PlaceModel * junction, PlaceModel * connectTarget, std::shared_ptr<RouteModel> opponent)
	{
		if (*opponent == *this)
			return;

		for (auto&& adjacenct : adjacentRoute)
		{
			std::shared_ptr<RouteModel> sptr = adjacenct.route.lock();

			if (sptr && *sptr == *opponent)
				return;
		}

		adjacentRoute.push_back(AdjacentRoute(junction, connectTarget, opponent));
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

		edge->BelongRoute(shared_from_this());
	}

	/**************************************
	端点設定
	***************************************/
	void RouteModel::SetEdge()
	{
		//始点から端点を設定
		PlaceModel* first = route.front();
		_SetEdge(first);

		//終点から端点を設定
		PlaceModel* last = route.back();
		_SetEdge(last);

		//各プレイスの方向を決定
		unsigned routeSize = route.size();

		first->AddDirection(first->IsAdjacent(edgeStart));
		first->AddDirection(first->IsAdjacent(route[1]));

		for (unsigned i = 1; i < routeSize - 1; i++)
		{
			PlaceModel* place = route[i];
			place->AddDirection(place->IsAdjacent(route[i - 1]));
			place->AddDirection(place->IsAdjacent(route[i + 1]));
		}

		last->AddDirection(last->IsAdjacent(route[routeSize - 2]));
		last->AddDirection(last->IsAdjacent(edgeEnd));
	}

	/**************************************
	他方の端点取得
	***************************************/
	PlaceModel * RouteModel::GetOtherEdge(const PlaceModel * edge)
	{
		if (edgeStart == edge)
			return edgeEnd;
		else
			return edgeStart;
	}

	/**************************************
	繋がっている街を取得
	***************************************/
	PlaceModel * RouteModel::GetConnectedTown(const PlaceModel * self)
	{
		if (edgeStart->IsType(PlaceType::Town) && edgeStart != self)
			return edgeStart;

		if (edgeEnd->IsType(PlaceType::Town) && edgeEnd != self)
			return edgeEnd;

		return nullptr;
	}

	/**************************************
	繋がっている街を取得
	***************************************/
	int RouteModel::FindLinkedTown(TownModel * root, std::vector<RouteModelPtr> & searchedRoute, std::vector<const PlaceModel*>& searchedTown, RoutePlaceStack& stackRoute, const PlaceModel* start)
	{
		int cntTown = 0;

		//ルートスタックに自身を積む
		int cntPush = stackRoute.Push(GetAllPlaces(start));

		//対象に繋がっている街を確認
		searchedRoute.push_back(shared_from_this());

		const PlaceModel* town = this->GetConnectedTown(root->GetPlace());
		if (town != nullptr)
		{
			cntTown++;
			searchedTown.push_back(town);

			//経路を保存
			root->AddLinkedRoute(stackRoute.route);
		}
		else
		{
			//隣接しているルートに対して再帰的に探索
			for (auto&& adjacency : this->adjacentRoute)
			{
				if (adjacency.start == start)
					continue;

				RouteModelPtr ptr = adjacency.route.lock();

				if (!ptr)
					continue;

				if (Utility::IsContain(searchedRoute, ptr))
					continue;

				cntTown += ptr->FindLinkedTown(root, searchedRoute, searchedTown, stackRoute, adjacency.end);
			}
		}
		//スタックから自身を取り除く
		stackRoute.Pop(cntPush);

		return cntTown;
	}

	/**************************************
	使用判定セット処理
	***************************************/
	void RouteModel::SetUnused(bool use)
	{
		isUnused = use;
	}

	/**************************************
	使用判定
	***************************************/
	bool RouteModel::IsUnused()
	{
		return isUnused;
	}

	/**************************************
	全プレイス取得
	***************************************/
	const std::vector<const PlaceModel*> RouteModel::GetAllPlaces(const PlaceModel* start) const
	{
		std::vector<const PlaceModel*> out;
		out.reserve(route.size() + 2);

		if (start == edgeEnd)
		{
			out.push_back(edgeEnd);
			std::copy(route.rbegin(), route.rend(), std::back_inserter(out));
			out.push_back(edgeStart);
		}
		else
		{
			out.push_back(edgeStart);

			std::copy(route.begin(), route.end(), std::back_inserter(out));
			out.push_back(edgeEnd);
		}

		return out;
	}

	/**************************************
	始点取得処理
	***************************************/
	PlaceModel * RouteModel::GetFirst() const
	{
		return route.front();
	}

	/**************************************
	終点取得処理
	***************************************/
	PlaceModel * RouteModel::GetLast() const
	{
		return route.back();
	}

	/**************************************
	端点設定（内部処理）
	***************************************/
	void RouteModel::_SetEdge(PlaceModel* place)
	{
		//連結相手を取得
		PlaceModel* opponent = place->GetEdgeOpponent();
		SetEdge(opponent);
		opponent->BelongRoute(shared_from_this());

		//街なら出口を増やす
		if (opponent->IsType(PlaceType::Town))
			(*onConnectedTown)(opponent);

		//交差点なら所属ルートを追加
	}

	/**************************************
	Placeプッシュ処理
	***************************************/
	bool RoutePlaceStack::Push(const PlaceModel * place)
	{
		//橋は追加しない
		if (place->IsType(PlaceType::Bridge))
			return false;

		if (place->IsType(PlaceType::Road))
		{
			std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
			StraightType straightType = IsStraight(AdjacencyType);

			//直線道なら追加しない
			if (straightType != StraightType::NotStraight)
				return false;
		}

		route.push_back(place->GetPosition().ConvertToWorldPosition());
		return true;
	}

	/**************************************
	Placeプッシュ処理
	***************************************/
	int RoutePlaceStack::Push(const std::vector<const PlaceModel*>& route)
	{
		int cntPush = 0;
		for (auto&& place : route)
		{
			if (Push(place))
				cntPush++;
		}

		return cntPush;
	}

	/**************************************
	Placeポップ処理
	***************************************/
	void RoutePlaceStack::Pop()
	{
		route.pop_back();
	}

	/**************************************
	Placeポップ処理
	***************************************/
	void RoutePlaceStack::Pop(int num)
	{
		route.resize(route.size() - num);
	}

	/**************************************
	サイズ取得処理
	***************************************/
	unsigned RoutePlaceStack::Size() const
	{
		return route.size();
	}
}