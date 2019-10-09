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
		//コンストラクタ、デストラクタ
		TownModel(const PlaceModel* place);
		~TownModel();

		//出口追加処理
		void AddGate();

		//出てくる人数の取得処理
		float DepatureNum();

		//出口数取得処理
		int GateNum();

		//リンクレベル計算処理
		int LinkLevel();

		//レベルが上がる際に呼ばれる処理
		float OnGrowth(float trafficJamRate);

	private:
		static const float BaseDepatureNum;		//基準となる出発数

		//ID
		static unsigned incrementID;
		const int uniqueID;

		//参照するプレイスモデル
		const PlaceModel* place;

		//出口数
		int cntGate;

		//リンクレベル
		int linkLevel;

		//発展度
		float developmentLevel;
	};
}
#endif