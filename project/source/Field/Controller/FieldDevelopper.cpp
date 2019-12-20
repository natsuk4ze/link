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
#include "../Place/FieldPlaceContainer.h"
#include "../../FieldObject/InfoController.h"
#include "../../Viewer/GameScene/Controller/FieldViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../Reward/RewardController.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"

#include "../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field
{
	/**************************************
	staticメンバ
	***************************************/
	const int FieldController::FieldDevelopper::MaxStock = 99;
	const int FieldController::FieldDevelopper::InitStock = 20;

	/**************************************
	コンストラクタ
	***************************************/
	FieldController::FieldDevelopper::FieldDevelopper(FieldController * controller) :
		entity(controller),
		stockNum(InitStock)
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
		using cpplinq::from;
		using cpplinq::intersect_with;
		using cpplinq::union_with;
		using cpplinq::except;
		using cpplinq::count;

		std::vector<PlaceModel*> route = entity->operateContainer->GetPlaces();
	
		if (route.size() > 1)
		{
			//両端が別のPlaceで無ければ早期リターン
			auto firstEdge = route.front()->GetEdgeOpponents();
			auto lastEdge = route.back()->GetEdgeOpponents();
			auto first = from(firstEdge);							//始点側の連結相手
			auto last = from(lastEdge);								//終点側の連結相手
			auto intersectList = first >> intersect_with(last);		//連結相手の積集合
			auto unionList = first >> union_with(last);				//連結相手の和集合

			//和集合から積集合を引いてXORを求める
			//XORの数が0ならルートがループしているのでリターン
			if (unionList >> except(intersectList) >> count() == 0)
				return;
		}

		int cntRoot = 0;
		//操作対象のプレイスをRoadタイプに変換
		for (auto&& place : route)
		{
			if (place->IsType(PlaceType::None))
				place->SetType(PlaceType::Road);

			cntRoot++;
		}

		//ルートモデル作成
		RouteModelPtr ptr = RouteModel::Create(entity->onConnectTown, route);

		//端点設定
		ptr->SetEdge();

		//隣接するルートと連結させる
		entity->routeProcessor->ConnectWithEdge(ptr, entity->routeContainer);
		entity->routeProcessor->Process(ptr, entity->routeContainer);

		//アクター生成
		entity->placeActController->SetActor(ptr);

		//リンクレベルを計算
		int prevLinkLevel = entity->placeContainer->GetPureLinkLevel();
		entity->placeContainer->CalcLinkLevel();

		//増加したリンクレベルを表示
		int currentLinkLevel = entity->placeContainer->GetPureLinkLevel();
		int diff = currentLinkLevel - prevLinkLevel;
		if (diff > 0)
		{
			SE::Play(SoundConfig::SEID::LinkLevelUpSE, 1.0f);
			entity->flgWaitPopup = true;
			entity->viewer->ViewLinkLevelUp(diff, [&]()
			{
				entity->flgWaitPopup = false;
			});

			GameParticleManager::Instance()->Generate(GameParticle::LinkLevelUp, { SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
		}

		// 接続されている全ての町のリンクレベルをセット
		entity->SetLinkLevelInfo();

		//コールバック
		entity->onBuildRoad(route);

		// リワードに反映
		RewardController::Instance()->SetRewardData(RC::Type::Pioneer, cntRoot);
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
		if (cntMountain <= stockNum)
		{
			for (auto&& place : container)
			{
				place->SetType(PlaceType::None);
				entity->placeActController->DestroyActor(place);
			}

			stockNum -= cntMountain;

			// リワードに反映
			RewardController::Instance()->SetRewardData(RC::Type::Destructer, cntMountain);

			//SE再生
			SE::Play(SoundConfig::SEID::Bom, 1.0f);
		}
		else
		{
			//エラーメッセージを再生
			entity->viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::StockShortage);
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

		//川の一つ前が橋ならそもそも架けられない
		if (start->IsType(PlaceType::Bridge))
			return route.end();

		//プレイスを前へ一つずつ確認していき終点を探す
		PlaceIterator end = route.end();
		for (auto itr = river + 1; itr != route.end(); itr++)
		{
			PlaceModel* prev = *(itr - 1);
			PlaceModel* place = *itr;
			Adjacency adjacency = place->IsAdjacent(prev);

			//隣接方向が直線になっていなければ早期リターン
			if (adjacency != startAdjacency)
			{
				entity->viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::CurveBridge);
				return itr;
			}

			//山が出てきたら早期リターン
			if (place->IsType(PlaceType::Mountain))
				return itr;

			//橋の場合は、連結できない方向であれば早期リターン
			if (place->IsType(PlaceType::Bridge))
			{
				std::vector<Adjacency> direction = place->GetConnectingAdjacency();

				if (!Utility::IsContain(direction, adjacency))
				{
					//エラーメッセージを表示
					entity->viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::BridgeConnection);
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
		if (cntRiver <= stockNum)
		{
			Adjacency inverseStartAdjacency = GetInverseSide(startAdjacency);
			for (auto&& river : riverVector)
			{
				river->SetType(PlaceType::Bridge);
				river->AddDirection(startAdjacency);
				river->AddDirection(inverseStartAdjacency);

				entity->placeActController->SetActor(river);
			}

			stockNum -= cntRiver;

			// リワードに反映
			RewardController::Instance()->SetRewardData(RC::Type::Artist, cntRiver);

			//SE再生
			SE::Play(SoundConfig::Fall, 1.0f);
		}
		else
		{
			//エラーメッセージを再生
			entity->viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::StockShortage);
		}

		return end;
	}

	/**************************************
	ストック加算処理
	***************************************/
	void FieldController::FieldDevelopper::AddStock(int num)
	{
		stockNum = Math::Min(MaxStock, stockNum + num);
	}

	/**************************************
	ストック数のリセット
	***************************************/
	void Field::FieldController::FieldDevelopper::ResetStock(void)
	{
		stockNum = InitStock;
	}

	/**************************************
	ストック数埋め込み処理
	***************************************/
	void FieldController::FieldDevelopper::EmbedViewerParam(GameViewerParam & param)
	{
		param.stockNum = stockNum;
	}
}