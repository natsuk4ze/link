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
#include "../../../Framework/Pattern/Delegate.h"

#include <vector>

namespace Field::Model
{
	/**************************************
	クラス定義
	***************************************/
	class RouteProcessor
	{
	public:
		//コンストラクタ、デストラクタ
		RouteProcessor(DelegatePtr<const PlaceModel*> onChangePlaceType);
		RouteProcessor() {}

		//新しく作ったルートに対して隣接しているルートと連結させて加工する
		void Process(RouteModelPtr& model, RouteContainer& routeContainer);

		//新しく作ったルートを端点で他と連結させる
		void ConnectWithEdge(RouteModelPtr& model, RouteContainer& routeContainer);

		//ルートをしていたプレイスで分割する
		RouteContainer Divide(RouteModelPtr& model, PlaceModel* junction, RouteContainer& routeContainer);

	private:
		//プレイスタイプを変化させた際のデリゲート
		DelegatePtr<const PlaceModel*> onChangePlaceType;

		void _ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer);
	};
}

#endif