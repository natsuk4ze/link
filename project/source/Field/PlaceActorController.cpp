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
#include "../../Framework/Task/TaskManager.h"
#include "../Effect/GameParticleManager.h"
#include "Along\AlongController.h"
#include "AStar\AStarController.h"
#include "../FieldObject/PassengerController.h"
#include "../../Framework/Resource/ResourceManager.h"

#include "Object/CityBackGroundContainer.h"
#include "Object/WorldBackGroundContainer.h"
#include "Object/SpaceBackGroundContainer.h"

#include "../FieldObject/Actor/CityActor.h"
#include "../FieldObject/Actor/CrossJunctionActor.h"
#include "../FieldObject/Actor/CurveRoadActor.h"
#include "../FieldObject/Actor/MountainActor.h"
#include "../FieldObject/Actor/RiverActor.h"
#include "../FieldObject/Actor/StraightRoadActor.h"
#include "../FieldObject/Actor/TJunctionActor.h"
#include "../FieldObject/Actor/BridgeActor.h"
#include "../FieldObject/Actor/NoneActor.h"

#include "../FieldObject/Animation/ActorAnimation.h"
#include "ActorLoader.h"
#include "../Field/Object/WaterHeightController.h"

namespace Field::Actor
{
	/**************************************
	using宣言
	***************************************/
	using Model::PlaceType;
	using Model::Adjacency;

	/**************************************
	staticメンバ
	***************************************/
	const float PlaceActorController::PlacePositionOffset = 10.0f;
	const D3DXVECTOR3 PlaceActorController::PositionEmitSmog = Vector3::Up;
	const unsigned PlaceActorController::ReserveGround = 2500;

	/**************************************
	コンストラクタ
	***************************************/
	PlaceActorController::PlaceActorController(Field::FieldLevel level) :
		currentLevel(level),
		bonusSideWay(0.0f)
	{
		alongController = new Along::AlongController(level);
		aStarController = new Route::AStarController();
		passengerController = new PassengerController(currentLevel);

		switch (level)
		{
		case FieldLevel::City:
			bgContainer = new CityBackGroundContainer();
			break;

		case FieldLevel::World:
			bgContainer = new WorldBackGroundContainer();
			break;

		case FieldLevel::Space:
			bgContainer = new SpaceBackGroundContainer();
			break;

		default:
			bgContainer = new CityBackGroundContainer();
			break;
		}

		auto onReachPassenger = std::bind(&Along::AlongController::OnReachPassenger, alongController, std::placeholders::_1);
		passengerController->SetCallbackOnReach(onReachPassenger);

		alongController->SetBuildBonusFunc([this]()
		{
			bonusSideWay += 1.0f;
		});

		//国レベルのモデルが無いので一旦、街レベルに落とす
		if (currentLevel == FieldLevel::World)
			currentLevel = FieldLevel::City;
	}

	/**************************************
	デストラクタ
	***************************************/
	PlaceActorController::~PlaceActorController()
	{
		SAFE_DELETE(alongController);
		SAFE_DELETE(aStarController);
		SAFE_DELETE(passengerController);
		SAFE_DELETE(bgContainer);

		actorContainer.clear();
	}

	/**************************************
	更新処理
	***************************************/
	void PlaceActorController::Update()
	{
		alongController->Update();
		passengerController->Update();

		WaterHeightController::UpdateHeight();
	
		bgContainer->Update();

		for (auto&& actor : actorContainer)
		{
			actor.second->Update();
		}

		for (auto&& actor : poolDestroy)
		{
			actor.second->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void PlaceActorController::Draw()
	{

		for (auto&& actor : actorContainer)
		{
			actor.second->Draw();
		}

		for (auto&& actor : poolDestroy)
		{
			actor.second->Draw();
		}

		alongController->Draw();
		passengerController->Draw();

		//bgContainer->Draw();
	}

	/**************************************
	リソース読み込み処理
	***************************************/
	void PlaceActorController::LoadResource()
	{
		// 3Dオブジェクトのリソースをロード
		ResourceManager::Instance()->LoadMesh("NoneActor", "data/MODEL/PlaceActor/ground.x");
		ResourceManager::Instance()->LoadMesh("River-City", "data/MODEL/PlaceActor/river.x");
		ResourceManager::Instance()->LoadMesh("AlongCity", "data/MODEL/AlongActor/AlongActorCity.x");
		ResourceManager::Instance()->LoadMesh("AlongSpace", "data/MODEL/AlongActor/AlongSpace.x");

		//アクターのリソースをロード
		ActorLoader loader;
		loader.LoadConfig();
		loader.LoadResource();

		//背景アクターをロード
		bgContainer->Load();

		// パッセンジャー
		passengerController->LoadResource();
		passengerController->LoadCSV(Field::Const::FieldLayerFile[0]);
	}

	/**************************************
	アクターセット処理
	***************************************/
	void PlaceActorController::SetActor(const Model::PlaceModel * place, int delay)
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

		case PlaceType::Road:
			SetRoad(place, delay);
			break;

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
		for (unsigned i = 1; i < PlaceMax; i++)
		{
			if (places[i]->IsType(PlaceType::Bridge))
				continue;

			SetActor(places[i], i * 2);
		}
	}

	/**************************************
	アクター切り替え処理
	***************************************/
	void PlaceActorController::ChangeActor(const Model::PlaceModel * place)
	{
		if (place == nullptr)
			return;

		if (place->IsType(PlaceType::Town))
			return;

		//アクター破棄
		EraseFromContainer(place->ID());

		SetActor(place);
	}

	/**************************************
	アクター消滅処理
	***************************************/
	bool PlaceActorController::DestroyActor(const Model::PlaceModel * place)
	{
		unsigned placeID = place->ID();

		if (actorContainer.count(placeID) == 0)
			return false;

		GameParticleManager::Instance()->Generate(GameParticle::WhiteSmog, place->GetPosition().ConvertToWorldPosition());

		//破棄プールへ移動してアクターコンテナから削除
		poolDestroy[placeID] = std::move(actorContainer[placeID]);
		actorContainer.erase(placeID);

		//アニメーションさせて終了時に解放
		ActorAnimation::Shrink(*poolDestroy[placeID], [&, placeID]()
		{
			poolDestroy.erase(placeID);
		});

		return true;
	}

	/**************************************
	道沿いのオブジェクト成長処理
	***************************************/
	void PlaceActorController::GrowthAlongObject(const D3DXVECTOR3 & position)
	{
		alongController->OnReachPassenger(position);
	}

	/**************************************
	街が繋がった
	***************************************/
	void PlaceActorController::OnConnectedTown(const Model::PlaceModel * place)
	{
		aStarController->OnChangePlace(place);
	}

	/**************************************
	パッセンジャー出発処理
	***************************************/
	void PlaceActorController::DepartPassenger(const Model::PlaceModel * start, const Model::PlaceModel * goal, const Model::PlaceModel* town)
	{
		auto route = aStarController->CalcRoute(start->GetPosition(), goal->GetPosition(), town->GetPosition());

		if (route.size() != 0)
		{
			passengerController->SetPassenger(route);
		}
	}

	/**************************************
	道沿いボーナス取得処理
	***************************************/
	float PlaceActorController::GetSideWayBonus() const
	{
		return bonusSideWay;
	}

	/**************************************
	海かどうかの判定
	***************************************/
	bool PlaceActorController::EnableAtlantis(const FieldPosition & position) const
	{
		return bgContainer->EnableAtlantis(position);
	}

	/**************************************
	新しい街作成
	***************************************/
	PlaceActor* PlaceActorController::CreateNewTown(const Model::PlaceModel * place)
	{
		//アクター生成
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();
		PlaceActor* actor = new CityActor(actorPos, currentLevel);

		AddContainer(place->ID(), actor);
		aStarController->OnChangePlace(place);

		Tween::Scale(*actor, { 0.25f, 0.0f, 0.25f }, { 0.25f, 0.25f, 0.25f }, 60, EaseType::InCubic);

		return actor;
	}

	/**************************************
	アトランティス出現
	***************************************/
	void PlaceActorController::SetAtlantis(const Model::PlaceModel * place)
	{
		//街作成
		const D3DXVECTOR3 InitOffset = Vector3::Down * 10.0f;
		PlaceActor* townActor = CreateNewTown(place);

		D3DXVECTOR3 actorPos = townActor->GetPosition();
		Tween::Move(*townActor, actorPos + InitOffset, actorPos, 60, EaseType::InOutCirc);

		//地面生成
		WorldBackGroundContainer *worldBgContainer = dynamic_cast<WorldBackGroundContainer*>(bgContainer);
		worldBgContainer->CreateAtlantis(place->GetPosition());

		//パッセンジャー側に地形の変化を通知
		passengerController->RewriteMap(place->GetPosition(), PassengerController::Geography::Ground);
	}

	/**************************************
	ロードセット処理
	***************************************/
	void PlaceActorController::SetRoad(const Model::PlaceModel * place, int delay)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//連結情報からどのタイプの道かを判定
		std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
		StraightType straightType = IsStraight(AdjacencyType);

		bool onWater = bgContainer->IsSeaPlace(place->GetPosition());

		//直線タイプの場合
		if (straightType != StraightType::NotStraight)
		{
			//アクター生成
			PlaceActor* actor = new StraightRoadActor(actorPos, currentLevel, onWater);
			AddContainer(place->ID(), actor);

			//左右に繋がるタイプなら回転させる
			if (straightType == StraightType::RightAndLeft)
				actor->Rotate(90.0f);

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::Straight);

			// 生成アニメーション
			actor->SetScale(Vector3::Zero);
			SetRoadGenerateAnimation(actor, actorPos, delay);
		}
		//カーブの場合
		else
		{
			//アクター生成
			PlaceActor* actor = new CurveRoadActor(actorPos, currentLevel, onWater);
			AddContainer(place->ID(), actor);

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

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::Curve);

			// 生成アニメーション
			actor->SetScale(Vector3::Zero);
			SetRoadGenerateAnimation(actor, actorPos, delay);
		}

		//A*に登録
		aStarController->OnChangePlace(place);
	}

	/**************************************
	タウンセット処理
	***************************************/
	void PlaceActorController::SetTown(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//アクター生成
		PlaceActor* actor = new CityActor(actorPos, currentLevel);

		// 生成アニメーション
		ActorAnimation::ExpantionYAndReturnToOrigin(*actor);

		AddContainer(place->ID(), actor);

		//A*に登録
		aStarController->OnChangePlace(place);
	}

	/**************************************
	ブリッジセット処理
	***************************************/
	void PlaceActorController::SetBridge(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//アクター生成
		PlaceActor* actor = new BridgeActor(actorPos, currentLevel);

		//回転角度を決定
		std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
		StraightType straightType = IsStraight(AdjacencyType);

		float rotateAngle = straightType == StraightType::BackAndForward ? 90.0f : 0.0f;

		//回転
		actor->Rotate(rotateAngle);

		// 生成アニメーション
		ActorAnimation::FallAndExpantion(*actor);

		AddContainer(place->ID(), actor);

		//A*に登録
		aStarController->OnChangePlace(place);
	}

	/**************************************
	交差点セット処理
	***************************************/
	void PlaceActorController::SetJunction(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		std::vector<Adjacency> adjacencyTypeList = place->GetConnectingAdjacency();

		bool onWater = bgContainer->IsSeaPlace(place->GetPosition());

		//十字路のアクター作成
		if (adjacencyTypeList.size() == 4)
		{
			PlaceActor *actor = new CrossJunctionActor(actorPos, currentLevel, onWater);

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::CrossJunction);

			// 生成アニメーション
			ActorAnimation::RotateAndExpantion(*actor);
			AddContainer(place->ID(), actor);

		}
		//T字路のアクター生成
		else
		{
			PlaceActor* actor = new TJunctionActor(actorPos, currentLevel, onWater);

			TjunctionType junctionType = IsTjunction(adjacencyTypeList);
			float rotAngle = 0.0f;

			if (junctionType == TjunctionType::ExceptRight)
				rotAngle = 90.0f;
			else if (junctionType == TjunctionType::ExceptForward)
				rotAngle = 180.0f;
			else if (junctionType == TjunctionType::ExceptLeft)
				rotAngle = 270.0f;

			actor->Rotate(rotAngle);

			AddContainer(place->ID(), actor);
			
			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::T_Junction);

			// 生成アニメーション
			ActorAnimation::RotateAndExpantion(*actor);
		}

		//A*に登録
		aStarController->OnChangePlace(place);
	}

	/**************************************
	山セット処理
	***************************************/
	void PlaceActorController::SetMountain(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		PlaceActor *actor = new MountainActor(actorPos, currentLevel);

		//回転
		float rotateAngle = Math::RandomRange(0, 4) * 90.0f;
		actor->Rotate(rotateAngle);

		//アニメーション
		ActorAnimation::ExpantionYAndReturnToOrigin(*actor);

		AddContainer(place->ID(), actor);
	}

	/**************************************
	コンテナ追加処理
	***************************************/
	void PlaceActorController::AddContainer(unsigned key, PlaceActor * actor)
	{
		//重複確認
		EraseFromContainer(key);

		actorContainer.emplace(key, std::unique_ptr<PlaceActor>(actor));
	}

	/**************************************
	コンテナからの削除処理
	***************************************/
	bool PlaceActorController::EraseFromContainer(unsigned key)
	{
		if (actorContainer.count(key) == 0)
			return false;

		//アクターコンテナから
		actorContainer.erase(key);

		return true;
	}

	/**************************************
	道生成時のアニメーションセット処理
	***************************************/
	void Field::Actor::PlaceActorController::SetRoadGenerateAnimation(PlaceActor * actor, const D3DXVECTOR3 actorPos, int delay)
	{
		if (delay == 0)
			ActorAnimation::FallAndExpantion(*actor, [=]()
		{
			GameParticleManager::Instance()->Generate(GameParticle::ColorfulDebis, actorPos + PositionEmitSmog);
		});

		else
		{
			TaskManager::Instance()->CreateDelayedTask(delay, [=]()
			{
				ActorAnimation::FallAndExpantion(*actor, [=]()
				{
					GameParticleManager::Instance()->Generate(GameParticle::ColorfulDebis, actorPos + PositionEmitSmog);
				});
			});
		}
	}
}