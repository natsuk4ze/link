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
#define DEBUG_PLACEMODEL

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

		//更新処理、描画処理
		void Update();
		void Draw();

		//座標取得
		FieldPosition GetPosition() const;

		//隣接プレイスの追加
		void AddAdjacency(PlaceModel *adjacency, Adjacency type);
	
		//ルートを始められるか
		bool CanStartRoute();

		//道に変えられるか
		bool ChangeableRoad();

		//開拓可能なタイプか
		bool IsDevelopableType();

		//placeと隣接しているか
		Adjacency IsAdjacent(PlaceModel* place);

		//連結できるタイプか
		bool IsConnectableType();

		//同じルートに属しているか
		bool IsSameRoute(PlaceModel* place);

		//連結対象の取得
		PlaceModel* GetConnectTarget();		//TODO:連結対象の複数化

		//端点となるPlaceの取得
		PlaceModel* GetEdgeOpponent();

		//ルートモデルへの所属、離脱
		void BelongRoute(std::shared_ptr<RouteModel> route);
		void BelongRoute(std::vector<std::shared_ptr<RouteModel>>& routes);
		void ExitRoute(std::shared_ptr<RouteModel> route);

		//タイプ判定、変更処理
		bool IsType(PlaceType type);
		void SetType(PlaceType type);

		//所属ルート取得
		RouteModelPtr GetConnectingRoute();
		RouteContainer GetConnectingRoutes();

	private:
		//ID
		static unsigned incrementID;
		unsigned uniqueID;

		//タイプ、座標
		PlaceType type;
		const FieldPosition Position;

		//所属しているルートの参照コンテナ
		std::vector<std::shared_ptr<RouteModel>> belongRouteList;

		//隣接プレイス
		std::vector<PlaceModel*> adjacencies;

		//ゲームに表示するアクター
		PlaceActor* actor;
	};
}

#endif