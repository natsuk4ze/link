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

		//リンクレベル取得処理
		int LinkLevel();

		//発展度取得処理
		float DevelopmentLevel();

		//レベルが上がる際に呼ばれる処理
		void FindLinkedTown();

		//リンクレベル加算処理
		void AddLinkLevel(int num);

		//プレイス取得処理
		const PlaceModel* GetPlace();

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

		//リンクレベルバイアス
		int biasLinkLevel;

		//発展度
		float developmentLevel;
	};
}
#endif