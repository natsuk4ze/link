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
	TownModel::TownModel(const PlaceModel* place, std::function<void(const PlaceModel *start, const PlaceModel *goal)> *action) :
		uniqueID(incrementID++),
		place(place),
		linkLevel(0),
		developmentLevel(0),
		biasLinkLevel(0),
		cntFrame(0),
		indexDestination(0),
		departPassenger(action)
	{
		gateList.reserve(4);
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
		
		if (linkedTown.size() == 0)
			return;

		//4秒おきに繋がっている街に向かってパッセンジャーを出発させる
		if (cntFrame % 30 == 0)
		{
			indexDestination = Math::WrapAround(0, (int)linkedTown.size(), ++indexDestination);
			(*departPassenger)(place, linkedTown[indexDestination]);
		}
	}

	/**************************************
	ゲート追加処理
	***************************************/
	void TownModel::AddGate(const PlaceModel* gate)
	{
		auto itr = std::find(gateList.begin(), gateList.end(), gate);

		if (itr == gateList.end())
		{
			gateList.push_back(gate);
		}
	}

	/**************************************
	出発人数取得処理
	***************************************/
	float TownModel::DepatureNum()
	{
		return 100.0f / gateList.size();
	}

	/**************************************
	ゲート数取得処理
	***************************************/
	int TownModel::GateNum()
	{
		return gateList.size();
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

		linkedTown.clear();
		for (auto&& route : belongRoute)
		{
			linkLevel += route->FindLinkedTown(this, searchedRoute, searchedTown, routeStack, place);
		}

		developmentLevel = (float)linkLevel /** linkLevel*/;
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
	void TownModel::AddLinkedTown(const PlaceModel *place)
	{
		linkedTown.push_back(place);
	}
}