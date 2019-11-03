//=====================================
//
//FieldPlaceModel.h
//機能:フィールド上のプレイスモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDPLACEMODEL_H_
#define _FIELDPLACEMODEL_H_

#include "../../../main.h"
#include "../FieldConfig.h"
#include "PlaceConfig.h"

#include <vector>

/**************************************
マクロ定義
***************************************/

/**************************************
前方宣言
***************************************/
class PlaceActor;

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class RouteModel;

	/**************************************
	クラス定義
	***************************************/
	class PlaceModel
	{
	public:
		//コンストラクタ、デストラクタ
		PlaceModel(PlaceType type, int x, int z);
		~PlaceModel();

		//座標取得
		FieldPosition GetPosition() const;

		//ID取得
		unsigned ID() const;

		//隣接プレイスの追加
		void AddAdjacency(PlaceModel *adjacency, Adjacency type);
	
		//ルートを始められるか
		bool CanStartRoute() const;

		//道に変えられるか
		bool ChangeableRoad(Adjacency prev) const;

		//開拓可能なタイプか
		bool IsDevelopableType() const;

		//placeと隣接しているか
		Adjacency IsAdjacent(const PlaceModel* place) const;

		//連結できるタイプか
		bool IsConnectableType() const;

		//同じルートに属しているか
		bool IsSameRoute(PlaceModel* place) const;

		//連結対象の取得
		PlaceModel* GetConnectTarget() const;		//TODO:連結対象の複数化

		//端点となるPlaceの取得
		PlaceModel* GetEdgeOpponent()  const;
		std::vector<PlaceModel*> GetEdgeOpponents() const;

		//ルートモデルへの所属、離脱
		void BelongRoute(std::shared_ptr<RouteModel> route);
		void BelongRoute(std::vector<std::shared_ptr<RouteModel>>& routes);
		void ExitRoute(std::shared_ptr<RouteModel> route);

		//タイプ判定、変更処理
		bool IsType(PlaceType type) const;
		void SetType(PlaceType type);
		const PlaceType GetType() const;
		const PlaceType GetPrevType() const;

		//所属ルート取得
		RouteModelPtr GetConnectingRoute() const;
		RouteContainer GetConnectingRoutes() const;

		//方向決定処理、取得処理
		void AddDirection(Adjacency direction);
		void AddDirection(PlaceModel* place);
		std::vector<Adjacency> GetConnectingAdjacency() const;

#ifdef DEBUG_PLACEMODEL
		//デバッグ用描画処理
		void DrawDebug();
#endif

	private:
		//ID
		static unsigned incrementID;
		unsigned uniqueID;

		//タイプ
		PlaceType type, prevType;

		//座標
		const FieldPosition Position;

		//所属しているルートの参照コンテナ
		std::vector<std::shared_ptr<RouteModel>> belongRouteList;

		//隣接プレイス
		std::vector<PlaceModel*> adjacencies;

		//連結方向
		std::vector<Adjacency> connectDirection;
	};
}

#endif