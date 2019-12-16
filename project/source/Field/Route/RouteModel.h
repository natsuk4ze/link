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
#include "../../../Framework/Pattern/Delegate.h"
#include "../Place/PlaceConfig.h"

#include <vector>
#include <functional>

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;
	class RouteModel;
	class TownModel;

	using RouteModelPtr = std::shared_ptr<RouteModel>;
	using CallbackConnect = std::function<void(const PlaceModel*, const PlaceModel*)>;

	
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
	class RouteModel : public std::enable_shared_from_this<RouteModel>
	{
		friend class RouteProcessor;
	public:
		//コンストラクタ
		RouteModel(CallbackConnect& onConnectTown);

		bool operator ==(const RouteModel& rhs) const;

		//Create関数でこのクラスのshared_ptrを作成させる
		static RouteModelPtr Create(CallbackConnect& onConnectTown);
		static RouteModelPtr Create(CallbackConnect& onConnectTown, const std::vector<PlaceModel*>& placeVector);

		//デストラクタ
		~RouteModel();		//所属を離脱

		//更新処理
		void Update();

		//ルートとなる道を追加
		void AddRoad(PlaceModel* place);

		//プレイスの所属解除
		void BreakAway();

		//隣接ルート追加
		void AddAdjacency(PlaceModel* junction, PlaceModel* connectTarget, std::shared_ptr<RouteModel> opponent);
	
		//端点設定
		void SetEdge();
		void SetEdge(PlaceModel* edge);

		//端点取得
		PlaceModel* GetOtherEdge(const PlaceModel* edge);

		//繋がっている街を取得
		PlaceModel* GetConnectedTown(const PlaceModel* self);

		//ルートに繋がっている街の探索
		int FindLinkedTown(TownModel* root, std::vector<unsigned>& searchedRoute);

		//使用判定
		void SetUnused(bool use);
		bool IsUnused();

		//全プレイス取得
		const std::vector<const PlaceModel*> GetAllPlaces(const PlaceModel* start = nullptr) const;

		//始点、終点取得処理
		PlaceModel* GetFirst() const;
		PlaceModel* GetLast() const;

		// 作った道の数を取得
		int GetRoadNum(void) { return this->route.size(); };

	private:
		PlaceModel *edgeStart, *edgeEnd;			//端点のPlace
		std::vector<PlaceModel*> route;				//道となるPlace
		std::vector<AdjacentRoute> adjacentRoute;	//隣接ルートのコンテナ

		static unsigned incrementID;				//インクリメントID
		unsigned uniqueID;							//インスタンス固有のID

		bool isUnused;								//使用判定

		CallbackConnect onConnectedTown;			//街と道が繋がったときのコールバック

		void _SetEdge(PlaceModel* place);			//端点設定内部処理
	};
}
#endif