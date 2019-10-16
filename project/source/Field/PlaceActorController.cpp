//=====================================
//
//PlaceActorController.cpp
//機能:プレイスアクターコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlaceActorController.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "FieldConfig.h"

#include "../FieldObject/Actor/CityActor.h"
#include "../FieldObject/Actor/CrossJunctionActor.h"
#include "../FieldObject/Actor/CurveRoadActor.h"
#include "../FieldObject/Actor/MountainActor.h"
#include "../FieldObject/Actor/RiverActor.h"
#include "../FieldObject/Actor/StraightRoadActor.h"
#include "../FieldObject/Actor/TJunctionActor.h"

namespace Field::Actor
{
	/**************************************
	using宣言
	***************************************/
	using Model::PlaceType;
	using Model::Adjacency;

	/**************************************
	using宣言
	***************************************/
	const float PlaceActorController::PlacePositionOffset = 10.0f;

	/**************************************
	コンストラクタ
	***************************************/
	PlaceActorController::PlaceActorController()
	{
		actorContainer.resize(ActorPattern::Max, NULL);

		for (auto&& actorMap : actorContainer)
		{
			actorMap = new ActorMap();
		}
	}

	/**************************************
	デストラクタ
	***************************************/
	PlaceActorController::~PlaceActorController()
	{
		for (auto&& actorMap : actorContainer)
		{
			actorMap->clear();
			SAFE_DELETE(actorMap);
		}
		actorContainer.clear();
	}

	/**************************************
	更新処理
	***************************************/
	void PlaceActorController::Update()
	{
		//for (auto&& map : actorMap)
		//{
		//	for (auto&& pair : *map)
		//	{
		//		pair.second->Update();
		//	}
		//}
	}

	/**************************************
	描画処理
	***************************************/
	void PlaceActorController::Draw()
	{
		//NOTE:インスタンシングで描画するために結構いじるかも
		for (auto&& map : actorContainer)
		{
			for (auto&& pair : *map)
			{
				pair.second->Draw();
			}
		}
	}

	/**************************************
	アクターセット処理
	***************************************/
	void PlaceActorController::SetActor(const Model::PlaceModel * place)
	{
		const Model::PlaceType Type = place->GetType();

		switch (Type)
		{
		case PlaceType::Bridge:
			SetBridge(place);
			break;

		case PlaceType::Junction:
			SetJunction(place);
			break;

		case PlaceType::Mountain:
			SetMountain(place);
			break;

		case PlaceType::River:
			SetRiver(place);
			break;

		case PlaceType::Road:
			SetRoad(place);

		case PlaceType::Town:
			SetTown(place);
			break;
		}
	}

	/**************************************
	アクターセット処理
	***************************************/
	void PlaceActorController::SetActor(const RouteModelPtr routeModel)
	{
		auto places = routeModel->GetAllPlaces();

		ChangeActor(places.front());
		ChangeActor(places.back());

		unsigned PlaceMax = places.size() - 1;
		for(unsigned i = 1; i < PlaceMax; i++)
		{ 
			SetActor(places[i]);
		}
	}

	/**************************************
	アクター切り替え処理
	***************************************/
	void PlaceActorController::ChangeActor(const Model::PlaceModel * place)
	{
		PlaceType PrevType = place->GetPrevType();
		unsigned PlaceID = place->ID();

		bool resultErase = false;

		//コンテナから使用中のアクターを削除
		if (PrevType == PlaceType::Road)
		{
			resultErase |= EraseFromContainer(ActorPattern::StarightRoad, PlaceID);
			resultErase |= EraseFromContainer(ActorPattern::Curve, PlaceID);
		}
		else if (PrevType == PlaceType::Junction)
		{
			resultErase |= EraseFromContainer(ActorPattern::TJunction, PlaceID);
			resultErase |= EraseFromContainer(ActorPattern::CrossJunction, PlaceID);
		}

		if (resultErase)
		{
			SetActor(place);
		}
	}

	/**************************************
	ロードセット処理
	***************************************/
	void PlaceActorController::SetRoad(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//連結情報からどのタイプの道かを判定
		std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
		StraightType straightType = IsStraight(AdjacencyType);

		//直線タイプの場合
		if (straightType != StraightType::NotStraight)
		{
			//アクター生成
			PlaceActor* actor = new StraightRoadActor(actorPos, Model::FieldLevel::City);

			//左右に繋がるタイプなら回転させる
			if (straightType == StraightType::RightAndLeft)
				actor->Rotate(90.0f);

			AddContainer(ActorPattern::StarightRoad, place->ID(), actor);
		}
		//カーブの場合
		else
		{
			//アクター生成
			PlaceActor* actor = new CurveRoadActor(actorPos, Model::FieldLevel::City);
			
			//回転角度を決定して回転
			float rotAngle = 0.0f;
			
			CurveType curveType = IsCurve(AdjacencyType);
			if (curveType == CurveType::LeftAndForward)
				rotAngle = -90.0f;
			else if (curveType == CurveType::BackAndRight)
				rotAngle = 90.0f;
			else if (curveType == CurveType::ForwardAndRight)
				rotAngle = 180.0f;

			actor->Rotate(rotAngle);

			AddContainer(ActorPattern::Curve, place->ID(), actor);
		}
	}

	/**************************************
	タウンセット処理
	***************************************/
	void PlaceActorController::SetTown(const Model::PlaceModel * place)
	{

	}

	/**************************************
	川セット処理
	***************************************/
	void PlaceActorController::SetRiver(const Model::PlaceModel * place)
	{
	}

	/**************************************
	ブリッジセット処理
	***************************************/
	void PlaceActorController::SetBridge(const Model::PlaceModel * place)
	{
	}

	/**************************************
	交差点セット処理
	***************************************/
	void PlaceActorController::SetJunction(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		std::vector<Adjacency> adjacencyTypeList = place->GetConnectingAdjacency();

		//十字路のアクター作成
		if (adjacencyTypeList.size() == 4)
		{
			PlaceActor *actor = new CrossJunctionActor(actorPos, Model::FieldLevel::City);
			AddContainer(ActorPattern::CrossJunction, place->ID(), actor);
		}
		//T字路のアクター生成
		else
		{
			PlaceActor* actor = new TJunctionActor(actorPos, Model::FieldLevel::City);
			
			TjunctionType junctionType = IsTjunction(adjacencyTypeList);
			float rotAngle = 0.0f;

			if (junctionType == TjunctionType::ExceptRight)
				rotAngle = 90.0f;
			else if (junctionType == TjunctionType::ExceptBack)
				rotAngle = 180.0f;
			else if (junctionType == TjunctionType::ExceptLeft)
				rotAngle = -90.0f;
	
			actor->Rotate(rotAngle);

			AddContainer(ActorPattern::TJunction, place->ID(), actor);
		}
	}

	/**************************************
	山セット処理
	***************************************/
	void PlaceActorController::SetMountain(const Model::PlaceModel * place)
	{
	}

	/**************************************
	コンテナ追加処理
	***************************************/
	void PlaceActorController::AddContainer(ActorPattern pattern, unsigned key, PlaceActor * actor)
	{
		actorContainer[pattern]->emplace(key, actor);
	}

	/**************************************
	コンテナからの削除処理
	***************************************/
	bool PlaceActorController::EraseFromContainer(ActorPattern pattern, unsigned key)
	{
		if (actorContainer[pattern]->count(key) == 0)
			return false;

		actorContainer[pattern]->erase(key);
		return true;
	}
}