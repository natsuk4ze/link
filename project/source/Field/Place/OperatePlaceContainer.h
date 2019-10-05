//=====================================
//
//OperatePlaceContainer.h
//機能:操作するプレイスを格納するコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _OPERATEPLACECONTAINER_H_
#define _OPERATEPLACECONTAINER_H_

#include "../../../main.h"
#include <vector>

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;

	/**************************************
	クラス定義
	***************************************/
	class OperatePlaceContainer
	{
	public:
		//コンストラクタ、デストラクタ
		OperatePlaceContainer();
		~OperatePlaceContainer();

		//プレイス追加開始処理
		bool Begin(PlaceModel* place);

		//プレイス追加処理
		bool Add(PlaceModel* place);

		//プレイス追加終了処理
		bool End();

		//コンテナクリア処理
		void Clear();

		//コンテナ取得処理
		std::vector<PlaceModel*> GetPlaces();

		//デバッグ表示
		void DrawDebug();

	private:
		std::vector<PlaceModel*> container;		//PlaceModelコンテナ
	};
}
#endif