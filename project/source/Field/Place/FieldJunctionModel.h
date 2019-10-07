//=====================================
//
//FieldJunctionModel.h
//機能:交差点のロジックモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDJUNCTIONMODEL_H_
#define _FIELDJUNCTIONMODEL_H_

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
	class JunctionModel
	{
	public:
		JunctionModel(const PlaceModel* place);
		~JunctionModel();

		float TrafficJam();

	private:
		static unsigned incrementID;
		const unsigned uniqueID;

		const PlaceModel* place;
	};
}
#endif