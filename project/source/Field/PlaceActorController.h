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

#include <vector>
#include <unordered_map>

/**************************************
前方宣言
***************************************/
class PlaceActor;
class TaskHandle;

namespace Field::Model
{
	class PlaceModel;
	class RouteModel;
}

namespace Field::Along
{
	class AlongController;
}

namespace Field::Actor
{
	/**************************************
	型エイリアス
	***************************************/
	using RouteModelPtr = std::shared_ptr<Field::Model::RouteModel>;
	using ActorContainer = std::unordered_map<unsigned, std::unique_ptr<PlaceActor>>;
	using BackGroundContainer = std::vector<std::unique_ptr<PlaceActor>>;

	/**************************************
	クラス定義
	***************************************/
	class PlaceActorController
	{
	public:
		PlaceActorController();
		~PlaceActorController();

		//更新処理、描画処理
		void Update();
		void Draw();

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

		//アクターコンテナ
		ActorContainer actorContainer;
		BackGroundContainer bgContainer;
		ActorContainer poolDestroy;

		//道沿いの情報コンテナ
		Along::AlongController *alongController;

		//各アクター生成処理
		void SetRoad(const Model::PlaceModel* place, int delay);
		void SetTown(const Model::PlaceModel* place);
		void SetRiver(const Model::PlaceModel* place);
		void SetBridge(const Model::PlaceModel* place);
		void SetJunction(const Model::PlaceModel* place);
		void SetMountain(const Model::PlaceModel* place);
		void SetNone(const Model::PlaceModel* place, float randomRange = 0.0f);

		//コンテナ追加、削除処理
		void AddContainer(unsigned key, PlaceActor* actor);
		bool EraseFromContainer(unsigned key);

		//アニメーションセット処理
		void SetRoadGenerateAnimation(PlaceActor* actor, const D3DXVECTOR3 actorPos, int delay = 0);
	};
}
#endif