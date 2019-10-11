
//=====================================
//
//RouteProcessor.cpp
//機能:ルートモデルを操作するクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RouteProcessor.h"
#include "RouteModel.h"
#include "../Place/FieldPlaceModel.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using宣言
	***************************************/
	using cpplinq::from;
	using cpplinq::contains;

	/**************************************
	コンストラクタ
	***************************************/
	RouteProcessor::RouteProcessor(DelegatePtr<const PlaceModel*> onChangePlaceType)
	{
		this->onChangePlaceType = onChangePlaceType;
	}

	/**************************************
	新しく作ったルートに対して隣接しているルートと連結させて加工する
	***************************************/
	void RouteProcessor::Process(RouteModelPtr & model, RouteContainer & routeContainer)
	{
		//分割したルートのリスト
		RouteContainer divideList;

		//対象のルートのPlaceに対して1個ずつ隣接ルートを確認する
		std::vector<PlaceModel*> route = model->route;
		int cnt = 0;
		for (auto&& place : route)
		{
			cnt++;
			PlaceModel* connectTarget = place->GetConnectTarget();

			//連結対象な見つからなかったのでコンティニュー
			if (connectTarget == nullptr)
				continue;

			//対象のPlaceを交差点にして分割
			place->SetType(PlaceType::Junction);
			divideList = Divide(model, place, routeContainer);
			(*model->onCreateJunction)(place);

			place->AddDirection(connectTarget);
			connectTarget->AddDirection(place);

			//繋がった相手も必要であれば分割する
			connectTarget->SetType(PlaceType::Junction);
			RouteContainer subDivList;
			if (connectTarget->GetPrevType() == PlaceType::Road)
			{
				(*model->onCreateJunction)(connectTarget);
				RouteModelPtr opponent = connectTarget->GetConnectingRoute();
				subDivList = Divide(opponent, connectTarget, routeContainer);
			}
			else
			{
				subDivList = connectTarget->GetConnectingRoutes();
			}

			//繋がったルート同士を隣接メンバとして保存
			for (auto&& own : divideList)
			{
				for (auto&& other : subDivList)
				{
					own->AddAdjacency(place, connectTarget, other);
					other->AddAdjacency(connectTarget, place, own);
				}
			}

			//相手を分割していればRouteContainerに追加
			if (subDivList.size() > 1)
			{
				std::copy(subDivList.begin(), subDivList.end(), std::back_inserter(routeContainer));
			}

			//所属を更新
			RouteContainer belongList = connectTarget->GetConnectingRoutes();
			place->BelongRoute(belongList);

			connectTarget->BelongRoute(divideList);

			//交差点と連結対象のオブジェクトを設定
			(*onChangePlaceType)(place);
			(*onChangePlaceType)(connectTarget);

			//ルートを分割した時点で正常にループできなくなるのでブレイク
			break;
		}

		//分割が行われていなかったらルートコンテナに追加
		if (divideList.empty())
		{
			routeContainer.push_back(model);
		}
		//分割が行われていたら再帰的に加工処理
		else
		{
			for (auto&& divModel : divideList)
			{
				Process(divModel, routeContainer);
			}
		}
	}

	/**************************************
	新しく作ったルートを端点で連結させる
	***************************************/
	void RouteProcessor::ConnectWithEdge(RouteModelPtr & model, RouteContainer & routeContainer)
	{
		//始点の連結を確認
		PlaceModel* start = model->edgeStart;
		if (start->IsType(PlaceType::Road) || start->IsType(PlaceType::Junction))
		{
			_ConnectWithEdge(model, start, routeContainer);
			start->AddDirection(model->edgeStart);
		}

		//終点の連結を確認
		PlaceModel* end = model->edgeEnd;
		if (end->IsType(PlaceType::Road) || end->IsType(PlaceType::Junction))
		{
			_ConnectWithEdge(model, end, routeContainer);
			end->AddDirection(model->edgeEnd);
		}
	}

	/**************************************
	ルートを指定したプレイスで分割する
	***************************************/
	RouteContainer RouteProcessor::Divide(RouteModelPtr & model, PlaceModel * junction, RouteContainer & routeContainer)
	{
		//分割後は使用しなくなるのでフラグを立てて、プレイスの所属を解除
		model->SetUnused(true);
		model->BreakAway();

		//交差点を基準にしてルートを分割
		std::vector<PlaceModel*> route = model->route;
		auto itrJunction = std::find(route.begin(), route.end(), junction);

		std::vector<PlaceModel*> firstHalf, secondHalf;
		firstHalf.assign(route.begin(), itrJunction);
		secondHalf.assign(itrJunction + 1, route.end());		//Junctionも含めないのでイテレータを+1

		//前半のRouteModelを作成
		RouteModelPtr first = RouteModel::Create(model->onConnectedTown, model->onCreateJunction, firstHalf);
		first->SetEdge(model->edgeStart);
		first->SetEdge(junction);

		//後半のRouteModelを作成
		RouteModelPtr second = RouteModel::Create(model->onConnectedTown, model->onCreateJunction, secondHalf);
		second->SetEdge(junction);
		second->SetEdge(model->edgeEnd);

		//分割前のルートの隣接ルートを取得
		std::vector<AdjacentRoute> adjacencies = model->adjacentRoute;

		//隣接情報作成
		first->AddAdjacency(adjacencies);
		first->AddAdjacency(junction, junction, second);

		second->AddAdjacency(adjacencies);
		second->AddAdjacency(junction, junction, first);

		//分割前に隣接していたルートに対して隣接情報を追加
		for (auto&& adjacency : adjacencies)
		{
			PlaceModel* connection = adjacency.start;

			//firstとsecondのどちらにconnectionが含まれているか判定
			RouteModelPtr opponent = from(firstHalf) >> contains(connection) ? first : second;

			std::shared_ptr<RouteModel> sptr = adjacency.route.lock();
			if (sptr)
			{
				sptr->AddAdjacency(adjacency.end, junction, opponent);
			}
		}

		//分割後のRouteModelをリストに追加
		RouteContainer routeList{ first, second };

		return routeList;
	}

	/**************************************
	連結処理（内部）
	***************************************/
	void RouteProcessor::_ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer)
	{
		//連結対象が道なら交差点にしてルートを分割
		place->SetType(PlaceType::Junction);
		if (place->GetPrevType() == PlaceType::Road)
		{
			(*model->onCreateJunction)(place);

			RouteContainer targetList = place->GetConnectingRoutes();

			//取得した所属リストに新しく作ったルートが含まれるので削除
			targetList.erase(std::remove(targetList.begin(), targetList.end(), model));

			//相手を分割
			RouteContainer divList = Divide(*targetList.begin(), place, routeContainer);
		}

		//連結相手と作ったルートの隣接情報を作成
		RouteContainer routeList = place->GetConnectingRoutes();
		for (auto&& route : routeList)
		{
			//NOTE:隣接の端点が同じなのはまずい
			model->AddAdjacency(place, place, route);
			route->AddAdjacency(place, place, model);
		}

		//所属を更新(内部で重複確認をしているので雑に突っ込む)
		//よく考えたらいらない気がするのでコメントアウト
		//place->BelongRoute(place->GetConnectingRoutes());

		//オブジェクト設定			
	}
}