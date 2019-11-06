//=====================================
//
//PlaceActorController.h
//機能:プレイスアクターコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLACEACTORCONTROLLER_H_
#define _PLACEACTORCONTROLLER_H_

#include "../../main.h"
#include "Place\PlaceConfig.h"
#include "FieldConfig.h"

#include <vector>
#include <unordered_map>

/**************************************
前方宣言
***************************************/
class PlaceActor;
class TaskHandle;
class PassengerController;

namespace Field::Model
{
	class PlaceModel;
	class RouteModel;
}

namespace Field::Along
{
	class AlongController;
}

namespace Field::Route
{
	class AStarController;
}

namespace Field::Actor
{
	/**************************************
	型エイリアス
	***************************************/
	using RouteModelPtr = std::shared_ptr<Field::Model::RouteModel>;
	using ActorContainer = std::unordered_map<unsigned, std::unique_ptr<PlaceActor>>;

	class BackGroundContainer;

	/**************************************
	クラス定義
	***************************************/
	class PlaceActorController
	{
	public:
		PlaceActorController(Field::FieldLevel level);
		~PlaceActorController();

		//更新処理、描画処理
		void Update();
		void Draw();

		void LoadResource();

		//アクター生成処理
		void SetActor(const Model::PlaceModel* place, int delay = 0);
		void SetActor(const RouteModelPtr routeModel);

		//アクター切り替え処理
		//既にアクターを生成している場合はこっちを呼ぶ
		void ChangeActor(const Model::PlaceModel* place);

		//アクター消滅処理
		bool DestroyActor(const Model::PlaceModel* place);

		//道沿いのモデル成長処理
		void GrowthAlongObject(const D3DXVECTOR3& position);

		//街が繋がった
		void OnConnectedTown(const Model::PlaceModel *place);

		//パッセンジャー出発処理
		void DepartPassenger(const Model::PlaceModel* start, const Model::PlaceModel* goal, const Model::PlaceModel* town);
		
		//道沿いボーナス取得設定
		float GetSideWayBonus() const;

		//海かどうかの判定
		bool IsSeaPlace(const FieldPosition& position) const;

		//定数メンバ
		static const D3DXVECTOR3 PositionEmitSmog;		//道落下時の煙発生位置
		static const float PlacePositionOffset;			//アクター同士の配置間隔
		static const unsigned ReserveGround;			//地面アクター用に予約するコンテナサイズ

	private:
		//アクターパターン列挙子
		enum ActorPattern
		{
			City,
			CrossJunction,
			TJunction,
			Curve,
			StarightRoad,
			Mountain,
			River,
			Bridge,
			None,
			Max
		};

		//フィールドレベル
		Field::FieldLevel currentLevel;

		//アクターコンテナ
		ActorContainer actorContainer;
		ActorContainer poolDestroy;

		//背景アクターコンテナ
		BackGroundContainer *bgContainer;

		//道沿いの情報コンテナ
		Along::AlongController *alongController;

		//A*コントローラ
		Route::AStarController *aStarController;

		//パッセンジャーコントローラ
		PassengerController *passengerController;

		//道造の発展ボーナス
		float bonusSideWay;

		//各アクター生成処理
		void SetRoad(const Model::PlaceModel* place, int delay);
		void SetTown(const Model::PlaceModel* place);
		void SetBridge(const Model::PlaceModel* place);
		void SetJunction(const Model::PlaceModel* place);
		void SetMountain(const Model::PlaceModel* place);

		//コンテナ追加、削除処理
		void AddContainer(unsigned key, PlaceActor* actor);
		bool EraseFromContainer(unsigned key);

		//アニメーションセット処理
		void SetRoadGenerateAnimation(PlaceActor* actor, const D3DXVECTOR3 actorPos, int delay = 0);
	};
}
#endif