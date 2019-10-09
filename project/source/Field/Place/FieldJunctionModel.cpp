//=====================================
//
//FieldJunctionModel.cpp
//機能:交差点のロジックモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldJunctionModel.h"
#include "FieldPlaceModel.h"
#include "FieldTownModel.h"
#include "../Route/RouteModel.h"

namespace Field::Model
{
	/**************************************
	staticメンバ
	***************************************/
	unsigned JunctionModel::incrementID = 0;

	/**************************************
	コンストラクタ
	***************************************/
	JunctionModel::JunctionModel(const PlaceModel * place) :
		uniqueID(incrementID++),
		place(place),
		trafficJam(0.0f)
	{

	}

	/**************************************
	デストラクタ
	***************************************/
	JunctionModel::~JunctionModel()
	{
	}

	/**************************************
	混雑度計算処理
	***************************************/
	void JunctionModel::Calculate(TownContainer & townContainer)
	{
		RouteContainer container = place->GetConnectingRoutes();

		//自身に流入してくる人数を確認
		float inflowNum = 0.0f;
		for (auto&& route : container)
		{
			PlaceModel* opponent = route->GetOtherEdge(place);

			if (!opponent->IsType(PlaceType::Town))
				continue;

			inflowNum += townContainer[opponent->ID()]->DepatureNum();
		}

		trafficJam = inflowNum;
	}

	/**************************************
	混雑度取得処理
	***************************************/
	float JunctionModel::TrafficJam(TownContainer& townContainer)
	{
		return trafficJam;
	}

}