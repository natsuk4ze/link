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
	TownModel::TownModel(const PlaceModel * place) :
		uniqueID(incrementID++),
		place(place),
		cntGate(0),
		linkLevel(0),
		developmentLevel(0),
		biasLinkLevel(0)
	{

	}

	/**************************************
	デストラクタ
	***************************************/
	TownModel::~TownModel()
	{
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
	成長する時に呼ばれる処理
	***************************************/
	float TownModel::OnGrowth(float trafficJamRate, float bonus)
	{
		linkLevel = 0;

		RouteContainer searchedRoute;
		std::vector<PlaceModel*> searchedTown;

		RouteContainer belongRoute = place->GetConnectingRoutes();
		for (auto&& route : belongRoute)
		{
			linkLevel += route->FindLinkedTown(place, searchedRoute, searchedTown);
		}

		//繋がっている街がなかったら補正計算を行わない
		if (linkLevel == 0)
			return 0.0f;

		int adjustLevel = Math::Max(1, linkLevel + biasLinkLevel);
		developmentLevel = (adjustLevel + adjustLevel * trafficJamRate) * bonus;
		return developmentLevel;
	}

	/**************************************
	リンクレベル加算処理
	***************************************/
	void TownModel::AddLinkLevel(int num)
	{
		biasLinkLevel += num;
	}

	const PlaceModel * TownModel::GetPlace()
	{
		return place;
	}
}