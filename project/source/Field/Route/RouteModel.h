//=====================================
//
//RouteModel.h
//機能:繋がった道を表すモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ROUTEMODEL_H_
#define _ROUTEMODEL_H_

#include "../../../main.h"

#include <vector>

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;
	class RouteModel;

	/**************************************
	隣接ルート情報
	***************************************/
	typedef struct _AdjacentRoute
	{
		PlaceModel *start, *end;
		std::weak_ptr<RouteModel> route;

		//コンストラクタ
		_AdjacentRoute(PlaceModel* start, PlaceModel* end, std::shared_ptr<RouteModel>& route) :
			start(start), end(end), route(route) {};

	}AdjacentRoute;

	/**************************************
	クラス定義
	***************************************/
	class RouteModel
	{
	public:
		//端点の種類を表す列挙子
		enum Edge
		{
			Start,		//始点
			End,		//終点
			Max
		};

		//コンストラクタ、デストラクタ
		RouteModel();
		RouteModel(const std::vector<PlaceModel*>& routes);
		~RouteModel();		//所属を離脱

		//更新処理
		void Update();

		//ルートとなる道を追加
		void AddRoad(PlaceModel* place);

		//隣接ルート追加
		void AddAdjacency(PlaceModel* junction, PlaceModel* connectTarget, std::shared_ptr<RouteModel> opponent);
		void AddAdjacency(const std::vector<AdjacentRoute>& adjacenctRoute);

		//隣接ルート取得
		std::vector<AdjacentRoute> GetAdjacencies();

		//端点設定
		void SetEdge();
		void SetEdge(PlaceModel* edge);

		//端点取得
		PlaceModel* GetEdge(Edge type);
		PlaceModel* GetOtherEdge(PlaceModel* edge);

		//繋がっている街を取得
		PlaceModel* GetConnectedTown(PlaceModel* self);

		//ルートとなるプレイスの取得
		std::vector<PlaceModel*> GetRoute();

	private:
		PlaceModel *edgeStart, *edgeEnd;			//端点のPlace
		std::vector<PlaceModel*> route;				//道となるPlace
		std::vector<AdjacentRoute> adjacentRoute;	//隣接ルートのコンテナ

		static unsigned incrementID;				//インクリメントID
		unsigned uniqueID;							//インスタンス固有のID

		void _SetEdge(PlaceModel* place);			//端点設定内部処理
	};
}
#endif