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
namespace Field::Model
{
	class PlaceModel;
	class RouteModel;
}

namespace Field::Actor
{
	/**************************************
	前方宣言
	***************************************/
	using RouteModelPtr = std::shared_ptr<Field::Model::RouteModel>;
	using ActorMap = std::unordered_map<unsigned, std::unique_ptr<PlaceActor>>;
	using ActorContainer = std::vector<ActorMap*>;

	/**************************************
	クラス定義
	***************************************/
	class PlaceActorController
	{
	public:
		PlaceActorController();
		~PlaceActorController();

		void Update();
		void Draw();

		void SetActor(const Model::PlaceModel* place);
		void SetActor(const RouteModelPtr routeModel);

		void ChangeActor(const Model::PlaceModel* place);
		
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
			Max
		};

		static const float PlacePositionOffset;

		ActorContainer actorContainer;

		inline D3DXVECTOR3 CalcActorPosition(const Model::PlaceModel* place);

		void SetRoad(const Model::PlaceModel* place);
		void SetTown(const Model::PlaceModel* place);
		void SetRiver(const Model::PlaceModel* place);
		void SetBridge(const Model::PlaceModel* place);
		void SetJunction(const Model::PlaceModel* place);
		void SetMountain(const Model::PlaceModel* place);

		void AddContainer(ActorPattern pattern, unsigned key, PlaceActor* actor);
		bool EraseFromContainer(ActorPattern pattern, unsigned key);
	};
}
#endif