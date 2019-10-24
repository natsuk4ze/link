//=====================================
//
//FieldDevelopper.cpp
//機能:フィールド開発機能
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldDevelopper.h"
#include "../Place/FieldPlaceModel.h"
#include "../PlaceActorController.h"
#include "../Place/OperatePlaceContainer.h"
#include "../Route/RouteModel.h"
#include "../Route/RouteProcessor.h"
#include "../Place/FieldPlaceContainer.h"

#include <algorithm>

namespace Field
{
	/**************************************
	コンストラクタ
	***************************************/
	FieldController::FieldDevelopper::FieldDevelopper(FieldController * controller) :
		entity(controller)
	{

	}

	/**************************************
	デストラクタ
	***************************************/
	FieldController::FieldDevelopper::~FieldDevelopper()
	{
	}

	/**************************************
	道を作る
	***************************************/
	void FieldController::FieldDevelopper::BuildRoad()
	{
		using namespace Field::Model;

		//操作対象のプレイスをRoadタイプに変換
		std::vector<PlaceModel*> route = entity->operateContainer->GetPlaces();
		for (auto&& place : route)
		{
			if (place->IsType(PlaceType::None))
				place->SetType(PlaceType::Road);
		}

		//ルートモデル作成
		RouteModelPtr ptr = RouteModel::Create(entity->onConnectTown, entity->onCreateJunction, route);

		//端点設定
		ptr->SetEdge();

		//オブジェクト設定

		//隣接するルートと連結させる
		entity->routeProcessor->ConnectWithEdge(ptr, entity->routeContainer);
		entity->routeProcessor->Process(ptr, entity->routeContainer);

		//道を新しく作ったので混雑度を再計算
		entity->placeContainer->CaclTrafficJamRate();

		//アクター生成
		entity->placeActController->SetActor(ptr);

		//コールバック
		(*entity->onBuildRoad)(route);
	}

	/**************************************
	プレイス開発処理
	***************************************/
	void FieldController::FieldDevelopper::DevelopPlace(PlaceVector & route, PlaceIterator start)
	{
		using namespace Field::Model;

		auto head = std::find_if(start, route.end(), [](auto& place)
		{
			return place->IsType(PlaceType::Mountain) || place->IsType(PlaceType::River);
		});

		//開拓対象が見つからないのでリターン
		if (head == route.end())
			return;

		//山を開拓
		if ((*head)->IsType(PlaceType::Mountain))
		{
			head = DevelopMountain(route, head);
		}
		//川を開拓
		else if ((*head)->IsType(PlaceType::River))
		{
			head = DevelopRiver(route, head);
		}

		//開拓が終了した位置から再帰的に開拓
		auto nextHead = std::find_if(head, route.end(), [](auto&& place)
		{
			//川じゃない、かつ、橋じゃないタイプを探す
			//NOTE:「山じゃない」も含めると、川と隣接した山を開拓できないので条件に含めない
			return !place->IsType(PlaceType::River) && !place->IsType(PlaceType::Bridge);
		});

		DevelopPlace(route, nextHead);
	}

	/**************************************
	山の開発処理
	***************************************/
	PlaceIterator FieldController::FieldDevelopper::DevelopMountain(PlaceVector & route, PlaceIterator mountain)
	{
		using namespace Field::Model;

		//対象のプレイスの前にある山以外のプレイスを探す
		auto start = std::find_if(ReversePlaceIterator(mountain), route.rend(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//山以外が見つからなかった場合は早期リターン
		if (start == route.rend())
		{
			return route.end();
		}

		//対象のプレイスの後ろにある山、川以外のプレイスを探す
		auto end = std::find_if(mountain, route.end(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//山以外が見つからなかったか、川の場合は早期リターン
		if (end == route.end())
		{
			return route.end();
		}

		//startとendを結ぶプレイスのコンテナを作成
		PlaceVector container;
		container.assign(start.base(), end);

		//ストックが足りていれば開拓
		int cntMountain = container.size();
		if (cntMountain <= entity->stockDevelopMountain)
		{
			for (auto&& place : container)
			{
				place->SetType(PlaceType::None);
			}

			entity->stockDevelopMountain -= cntMountain;
		}
		else
		{
			//エラーメッセージを再生
		}

		return end + 1;
	}

	/**************************************
	川の開発処理
	***************************************/
	PlaceIterator FieldController::FieldDevelopper::DevelopRiver(PlaceVector & route, PlaceIterator river)
	{
		using namespace Field::Model;

		//川の一つ前のプレイス（始点）がどの方向で隣接しているか確認
		PlaceModel* start = *(river - 1);
		Adjacency startAdjacency = (*river)->IsAdjacent(start);

		//プレイスを前へ一つずつ確認していき終点を探す
		PlaceIterator end = route.end();
		for (auto itr = river + 1; itr != route.end(); itr++)
		{
			PlaceModel* prev = *(itr - 1);
			PlaceModel* place = *itr;
			Adjacency adjacency = place->IsAdjacent(prev);

			//隣接方向が直線になっていなければ早期リターン
			if (adjacency != startAdjacency)
				return itr;

			//山が出てきたら早期リターン
			if (place->IsType(PlaceType::Mountain))
				return itr;

			//橋の場合は、連結できない方向であれば早期リターン
			if (place->IsType(PlaceType::Bridge))
			{
				std::vector<Adjacency> direction = place->GetConnectingAdjacency();

				if (!Utility::IsContain(direction, adjacency))
				{
					return itr;
				}
			}

			//橋を架けられるタイプであればブレーク
			if (!place->IsDevelopableType())
			{
				end = itr;
				break;
			}
		}

		//終点が見つからなかったので早期リターン
		if (end == route.end())
			return route.end();

		//始点と終点の間の川コンテナを作成
		PlaceVector riverVector;
		riverVector.assign(river, end);

		//ストックが足りていれば開拓
		int cntRiver = riverVector.size();
		if (cntRiver <= entity->stockDevelopRiver)
		{
			Adjacency inverseStartAdjacency = GetInverseSide(startAdjacency);
			for (auto&& river : riverVector)
			{
				river->SetType(PlaceType::Bridge);
				river->AddDirection(startAdjacency);
				river->AddDirection(inverseStartAdjacency);

				entity->placeActController->SetActor(river);
			}

			entity->stockDevelopRiver -= cntRiver;
		}
		else
		{
			//エラーメッセージの再生
		}

		return end;
	}

}