//=====================================
//
//FieldController.cpp
//機能:フィールドコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldController.h"
#include "FieldCursor.h"
#include "FieldGround.h"
#include "Place\FieldPlaceContainer.h"
#include "Place\OperatePlaceContainer.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "Route\RouteProcessor.h"
#include "PlaceActorController.h"

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../Event/EventController.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

#include <algorithm>

namespace Field
{
	/**************************************
	staticメンバ
	***************************************/
	const float FieldController::PlaceOffset = 10.0f;				//Placeの1マス毎のオフセット値
	const int FieldController::InitFieldBorder = 30;				//フィールド範囲の初期値
	const int FieldController::InputLongWait = 15;					//入力リピートの待機フレーム
	const int FieldController::InputShortWait = 5;					//入力リピートの待機フレーム
	const unsigned FieldController::InitDevelopRiverStock = 10;		//川開発ストックの初期数
	const unsigned FieldController::InitDevelopMountainStock = 10;	//山開発ストックの初期数
	const int FieldController::DevelopmentInterval = 30;			//発展レベル上昇のインターバル

	/**************************************
	コンストラクタ
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder),
		inputRepeatCnt(0),
		cntFrame(0),
		developmentLevelAI(0),
		stockDevelopRiver(InitDevelopRiverStock),
		stockDevelopMountain(InitDevelopMountainStock),
		stockEDF(0),
		stockInsurance(0),
		developSpeedBonus(1.0f),
		onConnectTown(nullptr),
		onCreateJunction(nullptr),
		onChangePlaceType(nullptr)
	{
		//インスタンス作成
		cursor = new FieldCursor(PlaceOffset);
		ground = new FieldGround();
		placeContainer = new Model::PlaceContainer();
		operateContainer = new Model::OperatePlaceContainer();
		placeActController = new Actor::PlaceActorController();

		//ステートマシン作成
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState();
		fsm[State::Develop] = new UseItemState();

		//デリゲート作成
		onConnectTown = Delegate<Model::PlaceContainer, const Model::PlaceModel*>::Create(placeContainer, &Model::PlaceContainer::OnConnectedTown);
		onCreateJunction = Delegate<Model::PlaceContainer, const Model::PlaceModel*>::Create(placeContainer, &Model::PlaceContainer::OnCreateJunction);
		onChangePlaceType = Delegate<Actor::PlaceActorController, const Model::PlaceModel*>::Create(placeActController, &Actor::PlaceActorController::ChangeActor);

		//ルートプロセッサ作成
		routeProcessor = new Model::RouteProcessor(onChangePlaceType);

		//ステート初期化
		ChangeState(State::Idle);
	}

	/**************************************
	デストラクタ
	***************************************/
	FieldController::~FieldController()
	{
		routeContainer.clear();

		//インスタンス削除
		SAFE_DELETE(cursor);
		SAFE_DELETE(ground);
		SAFE_DELETE(placeContainer);
		SAFE_DELETE(operateContainer);
		SAFE_DELETE(routeProcessor);
		SAFE_DELETE(placeActController);

		//デリゲート削除
		SAFE_DELETE(onConnectTown);
		SAFE_DELETE(onCreateJunction);
		SAFE_DELETE(onChangePlaceType);

		//ステートマシン削除
		Utility::DeleteContainer(fsm);
	}

	/**************************************
	更新処理
	***************************************/
	void FieldController::Update()
	{
		//使わなくなったルートコンテナを削除
		auto itr = std::remove_if(routeContainer.begin(), routeContainer.end(), [](auto& ptr)
		{
			return ptr->IsUnused();
		});
		routeContainer.erase(itr, routeContainer.end());

		//各更新処理
		cursor->Update();
		placeContainer->Update();

		for (auto&& route : routeContainer)
		{
			route->Update();
		}

		placeActController->Update();

		//AI発展レベルを計算
		CalcDevelopmentLevelAI();

		Debug::Log("ControllerState:%d", current);
		Debug::Log("StockRiver:%d", stockDevelopRiver);
		Debug::Log("StockMountain:%d", stockDevelopMountain);
		Debug::Log("DevelopmentAILevel:%d", (int)developmentLevelAI);
	}

	/**************************************
	描画処理
	***************************************/
	void FieldController::Draw()
	{
		ground->Draw();

		placeActController->Draw();

#ifdef DEBUG_PLACEMODEL
		operateContainer->DrawDebug();
		placeContainer->DrawDebug();
#endif
		//カーソルには透過オブジェクトが含まれるので最後に描画
		cursor->Draw();
	}

	/**************************************
	入力確認処理
	TODO：読み込むデータを選択できるようにする
	***************************************/
	void FieldController::Load()
	{
		placeContainer->LoadCSV("data/FIELD/sample01.csv");

		//カーソルのフィールドの中央へ設定
		FieldPosition border = placeContainer->GetPlaceBorder();
		cursor->SetModelPosition(border.x / 2, border.z / 2);

		//NOTE:今はまだ移動範囲の拡大処理が無いのでここで移動範囲を決定してしまう
		cursor->SetBorder(border.z - 1, border.x - 1, 0, 0);
	}

	/**************************************
	入力確認処理
	***************************************/
	void FieldController::CheckInput()
	{
		//トリガー確認
		float triggerX = 0.0f, triggerZ = 0.0f;

		triggerX = Input::GetTriggerHorizontal();
		triggerZ = -Input::GetTriggerVertical();

		//リピート確認
		float repeatX = 0.0f, repeatZ = 0.0f;
		if ((Input::GetPressHorizontail() != 0.0f || Input::GetPressVertical() != 0.0f))
		{
			inputRepeatCnt++;
			if (inputRepeatCnt >= InputLongWait && inputRepeatCnt % InputShortWait == 0)
			{
				repeatX = Input::GetPressHorizontail();
				repeatZ = -Input::GetPressVertical();
			}
		}
		else
		{
			inputRepeatCnt = 0;
		}

		//カーソルを移動
		float x = Math::Clamp(-1.0f, 1.0f, triggerX + repeatX);
		float z = Math::Clamp(-1.0f, 1.0f, triggerZ + repeatZ);
		cursor->Move((int)x, (int)z);

		//現在のステートの更新処理を実行
		State next = state->OnUpdate(*this);
		if (next != current)
		{
			ChangeState(next);
		}
	}

	/**************************************
	カーソル取得処理
	***************************************/
	GameObject * FieldController::GetFieldCursor()
	{
		return cursor;
	}

	/**************************************
	ビューワパラメータ埋め込み処理
	***************************************/
	void FieldController::EmbedViewerParam(GameViewerParam & param)
	{
		param.levelAI = (int)developmentLevelAI;
		param.ratioLevel = (float)developmentLevelAI / 9999.0f;
		param.stockBreakItem = stockDevelopMountain;
		param.stockBuildItem = stockDevelopRiver;
		param.stockEDF = stockEDF;
		param.stockInsurance = stockInsurance;
	}

	/**************************************
	AI発展レベルを増やす
	***************************************/
	void FieldController::AddLevelAI(float num)
	{
		float MaxLevel = 9999.0f;
		developmentLevelAI = Math::Clamp(0.0f, MaxLevel, developmentLevelAI + num);
	}

	/**************************************
	街の発展レベルを増やす
	***************************************/
	void FieldController::AddLevelDevelopment(float num)
	{
		placeContainer->AddDevelopmentLevel(num);
	}

	/**************************************
	ストックアイテムの数を増やす
	***************************************/
	void FieldController::AddStockItem(int num)
	{
		unsigned StockMax = 50;
		stockDevelopMountain = Math::Clamp((unsigned)0, StockMax, stockDevelopMountain + num);
		stockDevelopRiver = Math::Clamp((unsigned)0, StockMax, stockDevelopRiver + num);
	}

	/**************************************
	発展スピードへのボーナス付与
	***************************************/
	void FieldController::SetDevelopSpeedBonus()
	{
		//TODO ; 解除処理を実装する
		//TODO : 公開倍率をちゃんと決める
		developSpeedBonus = 1.5f;
	}

	/**************************************
	新しい街を出現させる
	***************************************/
	void FieldController::CreateNewTown()
	{
		//NOTE:後で作る
	}

	/**************************************
	街を破壊する
	***************************************/
	void FieldController::DestroyTown()
	{
		//NOTE：後で作る
	}

	/**************************************
	操作を反転させる
	***************************************/
	void FieldController::ReverseOperation(bool isReverse)
	{
		//InputControllerを作ってから
	}

	/**************************************
	ストックアイテム使用を封印する
	***************************************/
	void FieldController::SealUsingItem(bool isSeal)
	{
		//Developperを作ってから
	}

	/**************************************
	混雑度を上昇させる
	***************************************/
	void FieldController::RaiseTrafficJam(float bias)
	{
		//TODO：解除処理を実装する
		placeContainer->SetTrafficjamBias(bias);
	}

	/**************************************
	ステート切り替え処理
	***************************************/
	void FieldController::ChangeState(State next)
	{
		if (fsm[next] == NULL)
			return;

		current = next;
		state = fsm[next];
		state->OnStart(*this);
	}

	/**************************************
	カーソル位置のプレイスを取得
	***************************************/
	Model::PlaceModel * FieldController::GetPlace()
	{
		return placeContainer->GetPlace(cursor->GetModelPosition());
	}

	/**************************************
	道を作る
	***************************************/
	void FieldController::BuildRoad()
	{
		using namespace Field::Model;

		//操作対象のプレイスをRoadタイプに変換
		std::vector<PlaceModel*> route = operateContainer->GetPlaces();
		for (auto&& place : route)
		{
			if (place->IsType(PlaceType::None))
				place->SetType(PlaceType::Road);
		}

		//ルートベクトルを渡す
		EventController::CheckEventHappen(route, City);

		//ルートモデル作成
		RouteModelPtr ptr = RouteModel::Create(onConnectTown, onCreateJunction, route);

		//端点設定
		ptr->SetEdge();

		//オブジェクト設定

		//隣接するルートと連結させる
		routeProcessor->ConnectWithEdge(ptr, routeContainer);
		routeProcessor->Process(ptr, routeContainer);

		//道を新しく作ったので混雑度を再計算
		placeContainer->CaclTrafficJamRate();

		//アクター生成
		placeActController->SetActor(ptr);
	}

	/**************************************
	川、山を開発する
	***************************************/
	void FieldController::DevelopPlace(PlaceVector& route, PlaceIterator start)
	{
		using namespace Field::Model;

		auto head = std::find_if(start, route.end(), [](auto& place)
		{
			//川の開拓処理を入れていないので一旦コメントアウト
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
			return !place->IsDevelopableType();
		});

		DevelopPlace(route, nextHead);
	}

	/**************************************
	山を開発する
	***************************************/
	PlaceIterator FieldController::DevelopMountain(PlaceVector & route, PlaceIterator mountain)
	{
		using namespace Field::Model;

		//対象のプレイスの前にある山,川以外のプレイスを探す
		auto start = std::find_if(ReversePlaceIterator(mountain), route.rend(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//山以外が見つからなかったか、川の場合は早期リターン
		if (start == route.rend() || (*(start + 1).base())->IsType(PlaceType::River))
		{
			return route.end();
		}

		//対象のプレイスの後ろにある山、川以外のプレイスを探す
		auto end = std::find_if(mountain, route.end(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//山以外が見つからなかったか、川の場合は早期リターン
		if (end == route.end() || (*end)->IsType(PlaceType::River))
		{
			return route.end();
		}

		//startとendを結ぶプレイスのコンテナを作成
		PlaceVector container;
		container.assign(start.base(), end);

		//ストックが足りていれば開拓
		unsigned cntMountain = container.size();
		if (cntMountain <= stockDevelopMountain)
		{
			for (auto&& place : container)
			{
				place->SetType(PlaceType::None);
			}

			stockDevelopMountain -= cntMountain;
		}
		else
		{
			//エラーメッセージを再生
		}

		return end + 1;
	}

	/**************************************
	川を開発する
	***************************************/
	PlaceIterator FieldController::DevelopRiver(PlaceVector & route, PlaceIterator river)
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

			//隣接方向が直線になっていなければ早期リターン
			if (place->IsAdjacent(prev) != startAdjacency)
				return itr;

			//開拓可能以外のタイプであればbreak
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
		unsigned cntRiver = riverVector.size();
		if (cntRiver <= stockDevelopRiver)
		{
			Adjacency inverseStartAdjacency = GetInverseSide(startAdjacency);
			for (auto&& river : riverVector)
			{
				river->SetType(PlaceType::Bridge);
				river->AddDirection(startAdjacency);
				river->AddDirection(inverseStartAdjacency);
			}

			stockDevelopRiver -= cntRiver;
		}
		else
		{
			//エラーメッセージの再生
		}

		return end;
	}

	/**************************************
	AI発展レベルの計算
	***************************************/
	void FieldController::CalcDevelopmentLevelAI()
	{
		cntFrame = Math::WrapAround((const int)0, DevelopmentInterval, cntFrame + 1);

		//レベルの上昇はDevelopmentIntervalおきに行う
		if (cntFrame != 0)
			return;

		float raiseValue = placeContainer->CalcDevelopmentLevelAI(developSpeedBonus);
		AddLevelAI(raiseValue);
	}
}