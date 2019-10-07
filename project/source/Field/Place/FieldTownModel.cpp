//=====================================
//
//FieldTownModel.cpp
//機能:街のロジックモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldTownModel.h"
#include "FieldPlaceModel.h"

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
	TownModel::TownModel(PlaceModel * place) :
		uniqueID(incrementID++),
		place(place),
		cntGate(0)
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
}