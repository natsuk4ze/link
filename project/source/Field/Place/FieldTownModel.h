//=====================================
//
//FieldTownModel.h
//機能:街のロジックモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDTOWNMODEL_H_
#define _FIELDTOWNMODEL_H_

#include "../../../main.h"

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;

	/**************************************
	クラス定義
	***************************************/
	class TownModel
	{
	public:
		TownModel(PlaceModel* place);
		~TownModel();

		void AddGate();

		float DepatureNum();

		int GateNum();

	private:
		static const float BaseDepatureNum;

		static unsigned incrementID;
		const int uniqueID;

		const PlaceModel* place;

		int cntGate;
	};
}
#endif