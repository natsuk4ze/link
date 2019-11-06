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
#include <algorithm>

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
	TownModel::TownModel(const PlaceModel* place, std::function<void(const PlaceModel *start, const PlaceModel *goal, const PlaceModel* town)> *action) :
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
		if (linkedTown.size() == 0)
			return;

		//4秒おきに繋がっている街に向かってパッセンジャーを出発させる
		const int Interval = 120;
		if (cntFrame % Interval == 0)
		{
			indexDestination = Math::WrapAround(0, (int)linkedTown.size(), ++indexDestination);
			(*departPassenger)(linkedTown[indexDestination].second, linkedTown[indexDestination].first, place);
		}

		cntFrame++;
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
		return linkLevel + biasLinkLevel;
	}

	/**************************************
	発展度取得処理
	***************************************/
	float TownModel::DevelopmentLevel()
	{
		return developmentLevel;
	}

	/**************************************
	繋がっている街を探す処理
	***************************************/
	void TownModel::FindLinkedTown()
	{
		linkLevel = 0;

		std::vector<unsigned> searchedRoute;

		linkedTown.clear();
		for(indexSearchingGate = 0; indexSearchingGate < gateList.size(); indexSearchingGate++)
		{
			auto routeList = gateList[indexSearchingGate]->GetConnectingRoutes();
			searchedRoute.clear();
			for (auto&& route : routeList)
			{
				route->FindLinkedTown(this, searchedRoute);
			}
		}

		developmentLevel = (float)linkLevel;
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
		//相手を既にカウント済みかどうか検索
		bool searchedTown = false;
		bool linkedSameRoute = false;

		for (auto&& route : linkedTown)
		{
			searchedTown |= route.first == place;
			linkedSameRoute |= searchedTown && (route.second == gateList[indexSearchingGate]);
		}

		//同じ街が繋がっていなければリンクレベルを増加
		if (!searchedTown)
			linkLevel++;

		//同じルートがなければ追加
		if (!linkedSameRoute)
			linkedTown.push_back(std::make_pair(place, gateList[indexSearchingGate]));
	}

	//=================================
	// 情報取得処理
	//=================================
	PlaceData TownModel::GetPlaceData()
	{
		FieldPosition pos = place->GetPosition();
		return { pos, (int)developmentLevel };
	}
}