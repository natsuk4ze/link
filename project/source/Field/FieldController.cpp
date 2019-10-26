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
#include "FieldEventHandler.h"

#include "Controller\FieldDevelopper.h"
#include "Controller\FieldInput.h"

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

#include <algorithm>

#include "../Effect/GameParticleManager.h"

namespace Field
{
	/**************************************
	staticメンバ
	***************************************/
	const float FieldController::PlaceOffset = 10.0f;				//Placeの1マス毎のオフセット値
	const int FieldController::InitFieldBorder = 30;				//フィールド範囲の初期値
	const int FieldController::DevelopmentInterval = 30;			//発展レベル上昇のインターバル
	const float FieldController::MaxDevelopmentLevelAI = 9999.0f;	//AI発展レベルの最大値

	/**************************************
	コンストラクタ
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder),
		cntFrame(0),
		developmentLevelAI(0),
		developSpeedBonus(1.0f),
		onConnectTown(nullptr),
		onCreateJunction(nullptr),
		onChangePlaceType(nullptr)
	{
		using Model::PlaceContainer;
		using Model::PlaceModel;

		//インスタンス作成
		cursor = new FieldCursor(PlaceOffset);
		ground = new FieldGround();
		placeContainer = new Model::PlaceContainer();
		operateContainer = new Model::OperatePlaceContainer();
		placeActController = new Actor::PlaceActorController();
		developper = new FieldDevelopper(this);
		input = new FieldInput(this);

		//ステートマシン作成
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState();
		fsm[State::Develop] = new UseItemState();

		//デリゲート作成
		onConnectTown = DelegateObject<PlaceContainer, void(const PlaceModel*)>::Create(placeContainer, &PlaceContainer::OnConnectedTown);
		onCreateJunction = DelegateObject<PlaceContainer, void(const PlaceModel*)>::Create(placeContainer, &PlaceContainer::OnCreateJunction);
		onChangePlaceType = DelegateObject<Actor::PlaceActorController, void(const PlaceModel*)>::Create(placeActController, &Actor::PlaceActorController::ChangeActor);

		//ルートプロセッサ作成
		routeProcessor = new Model::RouteProcessor(onChangePlaceType);

		//制限時間初期化
		//TODO:シーンを跨いで引き継げるようにする

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
		SAFE_DELETE(developper);
		SAFE_DELETE(input);

		//デリゲート削除
		SAFE_DELETE(onConnectTown);
		SAFE_DELETE(onCreateJunction);
		SAFE_DELETE(onChangePlaceType);

		//ステートマシン削除
		Utility::DeleteContainer(fsm);
	}

	/**************************************
	オブジェクト更新処理
	***************************************/
	void FieldController::UpdateObject()
	{
		//各更新処理
		cursor->Update();
		placeContainer->Update();

		placeActController->Update();
	}

	/**************************************
	ロジック更新処理
	***************************************/
	void FieldController::UpdateLogic()
	{
		//使わなくなったルートコンテナを削除
		auto itr = std::remove_if(routeContainer.begin(), routeContainer.end(), [](auto& ptr)
		{
			return ptr->IsUnused();
		});
		routeContainer.erase(itr, routeContainer.end());

		for (auto&& route : routeContainer)
		{
			route->Update();
		}

		//AI発展レベルを計算
		CalcDevelopmentLevelAI();
	}

	/**************************************
	描画処理
	***************************************/
	void FieldController::Draw()
	{
		//ground->Draw();

		placeActController->Draw();

#ifdef DEBUG_PLACEMODEL
		operateContainer->DrawDebug();
		placeContainer->DrawDebug();
#endif
		//カーソルには透過オブジェクトが含まれるので最後に描画
		cursor->Draw();
	}

	/**************************************
	CSV読み込み処理
	TODO：読み込むデータを選択できるようにする
	***************************************/
	void FieldController::Load()
	{
		placeContainer->LoadCSV("data/FIELD/sample01.csv");

		//アクター生成
		auto places = placeContainer->GetAllPlaces();
		for (auto&& place : places)
		{
			placeActController->SetActor(place);
		}

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
		input->CheckMoveInput();
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
		param.ratioLevel = (float)developmentLevelAI / MaxDevelopmentLevelAI;
		developper->EmbedViewerParam(param);
	}

	/**************************************
	道作成時のデリゲータ設定処理
	***************************************/
	void FieldController::SetCallbackOnBuildRoad(Delegate<void(std::vector<Model::PlaceModel*>&)> *callback)
	{
		onBuildRoad = callback;
	}

	/**************************************
	レベルアップするかどうかの判定
	***************************************/
	bool FieldController::ShouldLevelUp()
	{
		return developmentLevelAI >= MaxDevelopmentLevelAI;
	}

	/**************************************
	イベントハンドラ作成処理
	***************************************/
	void FieldController::SetEventHandler(::FieldEventHandler& handler)
	{
		using Handler = ::FieldEventHandler;

		//AI発展レベル調整ファンクタ
		handler.functerFloat[Handler::FuncterID_float::AdjustAI] = [&](float percent)
		{
			float delta = developmentLevelAI * percent;
			developmentLevelAI = Math::Clamp(0.0f, 9999.0f, developmentLevelAI + delta);
		};

		//AI発展レベル加算ファンクタ
		handler.functerFloat[Handler::FuncterID_float::AddAI] = [&](float num)
		{
			developmentLevelAI = Math::Clamp(0.0f, 9999.0f, developmentLevelAI + num);
		};

		//全体リンクレベル調整ファンクタ
		handler.functerInt[Handler::FuncterID_int::AdjustLinkAll] = [&](int num)
		{
			placeContainer->AddAllLinkLevel(num);
		};

		//単体リンクレベル調整ファンクタ
		handler.functerInt[Handler::FuncterID_int::AdjustLink] = [&](int num)
		{
			placeContainer->AddLinkLevel(num);
		};

		//アイテムストック加算ファンクタ
		handler.functerInt[Handler::FuncterID_int::AddStock] = [&](int num)
		{
			developper->AddStock(num);
		};

		//発展倍率付与ファンクタ
		handler.functerFloat[Handler::FuncterID_float::SetDevBonus] = [&](float percent)
		{
			developSpeedBonus = percent;
		};

		//街作成ファンクタ
		handler.functerPlace[Handler::FuncterID_Place::Create] = [&](auto place)
		{
			//後で作る
		};

		//街破壊ファンクタ
		handler.functerPlace[Handler::FuncterID_Place::Destroy] = [&](auto place)
		{
			placeContainer->DestroyTown(place);
			placeActController->DestroyActor(place);
		};

		//操作反転処理
		handler.functerBool[Handler::FuncterID_bool::ReverseOpe] = [&](bool isReverse)
		{
			input->ReverseOperate(isReverse);
		};

		//ストック封印処理
		handler.functerBool[Handler::FuncterID_bool::SealItem] = [&](bool isSeal)
		{
			//後で作る
		};

		//混雑度調整処理
		handler.functerFloat[Handler::FuncterID_float::AdjustTraffic] = [&](float bias)
		{
			placeContainer->SetTrafficjamBias(bias);
		};

		//EDFストック使用処理
		handler.functerBoolReturn[Handler::FuncterID_boolReturn::TryEDF] = [&]()
		{
			return false;
		};

		//保険ストック使用処理
		handler.functerBoolReturn[Handler::FuncterID_boolReturn::TryInsurance] = [&]()
		{
			return false;
		};

		//破壊対象の街取得処理
		handler.functerPlaceReturn[Handler::FuncterID_PlaceReturn::DestroyTarget] = [&]()
		{
			return placeContainer->GetDestroyTarget();
		};

		//街作成予定地の取得処理
		handler.functerPlaceReturn[Handler::FuncterID_PlaceReturn::PlacePosition] = [&]()
		{
			return placeContainer->GetNonePlace();
		};
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
	AI発展レベルの計算
	***************************************/
	void FieldController::CalcDevelopmentLevelAI()
	{
		cntFrame = Math::WrapAround((const int)0, DevelopmentInterval, cntFrame + 1);

		//レベルの上昇はDevelopmentIntervalおきに行う
		if (cntFrame != 0)
			return;

		float raiseValue = placeContainer->CalcDevelopmentLevelAI(developSpeedBonus);
		developmentLevelAI = Math::Clamp(0.0f, 9999.0f, developmentLevelAI + raiseValue);
	}
}