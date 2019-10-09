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
#include <unordered_map>

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;
	class TownModel;

	/**************************************
	クラス定義
	***************************************/
	class JunctionModel
	{
	public:
		using TownContainer = std::unordered_map<unsigned, TownModel*>;

		//コンストラクタ、デストラクタ
		JunctionModel(const PlaceModel* place);
		~JunctionModel();

		//混雑度計算処理
		void Calculate(TownContainer& townContainer);

		//混雑度取得処理
		float TrafficJam(TownContainer& townContainer);

	private:
		//ID
		static unsigned incrementID;
		const unsigned uniqueID;

		//参照するプレイスモデル
		const PlaceModel* place;

		//混雑度
		float trafficJam;
	};
}
#endif