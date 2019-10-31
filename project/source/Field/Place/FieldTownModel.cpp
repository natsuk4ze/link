//=====================================
//
//FieldTownModel.cpp
//機能:街のロジックモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldTownModel.h"
#include "FieldPlaceModel.h"
#include "../Route/RouteModel.h"

namespace Field::Model
{
	/**************************************
	staticメンバ
	***************************************/
	unsigned TownModel::incrementID = 0;
	const float TownModel::BaseDepatureNum = 100.0f;

	/**************************************
	コンストラクタ
	***************************************/
	TownModel::TownModel(const PlaceModel * place, std::function<void(std::vector<D3DXVECTOR3>&)> *action) :
		uniqueID(incrementID++),
		place(place),
		cntGate(0),
		linkLevel(0),
		developmentLevel(0),
		biasLinkLevel(0),
		cntFrame(0),
		indexDestination(0),
		departPassenger(action)
	{

	}

	/**************************************
	デストラクタ
	***************************************/
	TownModel::~TownModel()
	{
	}

	/**************************************
	更新処理
	***************************************/
	void TownModel::Update()
	{
		cntFrame++;

		if (routeContainer.size() == 0)
			return;

		//4秒おきに繋がっている街に向かってパッセンジャーを出発させる
		if (cntFrame % 120 == 0)
		{
			indexDestination = Math::WrapAround(0, (int)routeContainer.size(), ++indexDestination);
			(*departPassenger)(routeContainer[indexDestination]);
		}
	}

	/**************************************
	ゲート追加処理
	***************************************/
	void TownModel::AddGate()
	{
		cntGate++;
	}

	/**************************************
	出発人数取得処理
	***************************************/
	float TownModel::DepatureNum()
	{
		return 100.0f / cntGate;
	}

	/**************************************
	ゲート数取得処理
	***************************************/
	int TownModel::GateNum()
	{
		return cntGate;
	}

	/**************************************
	リンクレベル取得処理
	***************************************/
	int TownModel::LinkLevel()
	{
		return linkLevel;
	}

	/**************************************
	発展度取得処理
	***************************************/
	float TownModel::DevelopmentLevel()
	{
		return developmentLevel;
	}

	/**************************************
	成長する時に呼ばれる処理
	***************************************/
	void TownModel::FindLinkedTown()
	{
		linkLevel = biasLinkLevel;

		RouteContainer searchedRoute;
		std::vector<const PlaceModel*> searchedTown;
		searchedTown.push_back(place);

		RouteContainer belongRoute = place->GetConnectingRoutes();

		RoutePlaceStack routeStack;

		routeContainer.clear();
		for (auto&& route : belongRoute)
		{
			linkLevel += route->FindLinkedTown(this, searchedRoute, searchedTown, routeStack, place);
		}

		developmentLevel = (float)linkLevel * linkLevel;
	}

	/**************************************
	リンクレベル加算処理
	***************************************/
	void TownModel::AddLinkLevel(int num)
	{
		biasLinkLevel += num;
	}

	/**************************************
	PlaceModel取得処理
	***************************************/
	const PlaceModel * TownModel::GetPlace()
	{
		return place;
	}

	/**************************************
	経路追加処理
	***************************************/
	void TownModel::AddLinkedRoute(std::vector<D3DXVECTOR3>& route)
	{
		//コピーして重複を削除
		std::vector<D3DXVECTOR3> container(route);
		auto itr = std::unique(container.begin(), container.end());
		container.erase(itr, container.end());

		bool shouldAdd = true;

		//目的地が同じルートが既にある場合は長さを比較
		for (auto&& route : routeContainer)
		{
			if (route.back() != container.back())
				continue;

			if (route.size() > container.size())
			{
				route = container;
			}

			shouldAdd = false;
		}

		if(shouldAdd)
			routeContainer.push_back(container);
	}
}