//=====================================
//
//RouteProcessor.h
//機能:ルートモデルを操作するクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ROUTEPROCESSOE_H_
#define _ROUTEPROCESSOE_H_

#include "../../../main.h"
#include "../Place/PlaceConfig.h"

#include <vector>

namespace Field::Model
{
	/**************************************
	クラス定義
	***************************************/
	class RouteProcessor
	{
	public:
		//新しく作ったルートに対して隣接しているルートと連結させて加工する
		static void Process(RouteModelPtr& model, RouteContainer& routeContainer);

		//新しく作ったルートを端点で他と連結させる
		static void ConnectWithEdge(RouteModelPtr& model, RouteContainer& routeContainer);

		//ルートをしていたプレイスで分割する
		static RouteContainer Divide(RouteModelPtr& model, PlaceModel* junction, RouteContainer& routeContainer);

		//ルートに繋がっている街の探索
		static int FindLinkedTown(const PlaceModel* root, RouteModelPtr target, RouteContainer& searchedRoute, std::vector<PlaceModel*> searchedTown);

	private:
		RouteProcessor() {}

		static void _ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer);
	};
}

#endif