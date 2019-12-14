//=====================================
//
//FieldController.cpp
//機能:フィールドコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldController.h"
#include "Object/FieldCursor.h"
#include "Object/FieldSkyBox.h"
#include "Place\FieldPlaceContainer.h"
#include "Place\OperatePlaceContainer.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "Route\RouteProcessor.h"
#include "PlaceActorController.h"
#include "FieldEventHandler.h"
#include "Controller\FieldDevelopper.h"
#include "Controller\FieldInput.h"
#include "../FieldObject/InfoController.h"
#include "../Viewer/GameScene/Controller/FieldViewer.h"
#include "../Score/Score.h"

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Tool/ProfilerCPU.h"
#include "../../Framework/Math//Easing.h"
#include "../../Framework/Core/PlayerPrefs.h"
#include "../GameConfig.h"

#include <algorithm>

#include "../Effect/GameParticleManager.h"
#include "../../Framework/Math/Easing.h"
#include "../Reward/RewardController.h"

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
	FieldController::FieldController(Field::FieldLevel level) :
		fieldBorder(InitFieldBorder),
		cntFrame(0),
		developmentLevelAI(0),
		developSpeedBonus(1.0f),
		currentLevel(level),
		operationZ(OperationExplanationViewer::OperationID::Z_None),
		operationX(OperationExplanationViewer::OperationID::X_None),
		operationSpace(OperationExplanationViewer::OperationID::Space_None),
		enableDevelop(true),
		flgWaitPopup(false)
	{
		using Model::PlaceContainer;
		using Model::PlaceModel;

		//リソース読み込み
		FieldSkyBox::LoadResource();
		Actor::PlaceActorController::LoadResource();

		//インスタンス作成
		cursor = new FieldCursor(PlaceOffset);
		operateContainer = new Model::OperatePlaceContainer();
		developper = new FieldDevelopper(this);
		input = new FieldInput(this);
		placeContainer = new Model::PlaceContainer();
		viewer = new FieldViewer();
		score = new Score();

		//フィールドレベル設定
		SetLevel(currentLevel);

		//ステートマシン作成
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState();
		fsm[State::Develop] = new UseItemState();

		//ファンクタ作成
		onConnectTown = std::bind(&FieldController::OnConnectedTown, this, std::placeholders::_1, std::placeholders::_2);
		onChangePlaceType = std::bind(&Actor::PlaceActorController::ChangeActor, placeActController, std::placeholders::_1);

		auto onDepartPassenger = std::bind(&Actor::PlaceActorController::DepartPassenger, placeActController, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		placeContainer->SetDepartPassengerFanctor(onDepartPassenger);

		auto onStartMorph = std::bind(&Actor::PlaceActorController::OnStartMorphing, placeActController, std::placeholders::_1, std::placeholders::_2);
		placeContainer->SetMorphingFantor(onStartMorph);

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
		SAFE_DELETE(skybox);
		SAFE_DELETE(cursor);
		SAFE_DELETE(placeContainer);
		SAFE_DELETE(operateContainer);
		SAFE_DELETE(routeProcessor);
		SAFE_DELETE(placeActController);
		SAFE_DELETE(developper);
		SAFE_DELETE(input);
		SAFE_DELETE(infoController);
		SAFE_DELETE(viewer);
		SAFE_DELETE(score);

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

		operateContainer->Update();

		placeActController->Update();

		infoController->Update();

		viewer->Update();

		//デバッグツール
		Debug::Begin("DebugTool");
		if (Debug::Button("LinkUp 5"))
		{
			viewer->ViewLinkLevelUp(5);
		}
		Debug::SameLine();
		if (Debug::Button("LinkUp 15"))
		{
			viewer->ViewLinkLevelUp(15);
		}
		if (Debug::Button("Field Error"))
		{
			viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::NotConnection);
		}
		Debug::End();
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
		skybox->Draw();

		placeActController->Draw();

#ifdef DEBUG_PLACEMODEL
		placeContainer->DrawDebug();
#endif
		//カーソルには透過オブジェクトが含まれるので最後に描画
		bool isSea = placeActController->IsOnSea(cursor->GetModelPosition());
		cursor->Draw(isSea);
		operateContainer->Draw();
	}

	/**************************************
	Info描画処理
	***************************************/
	void FieldController::DrawInfo()
	{
		infoController->Draw();
	}

	/**************************************
	UI描画処理
	***************************************/
	void FieldController::DrawViewer()
	{
		if (!isViewerActive)
			return;

		SetOperationExplanation();
		viewer->Draw();
	}

	/**************************************
	フィールドレベル設定処理
	***************************************/
	void FieldController::SetLevel(Field::FieldLevel level)
	{
		LARGE_INTEGER start, end;

		currentLevel = level;

		//フィールドレベルが関係するインスタンスを作成
		start = ProfilerCPU::GetCounter();
		skybox = new FieldSkyBox(level);
		end = ProfilerCPU::GetCounter();

		Debug::Log("Create Skybox : %f", ProfilerCPU::CalcElapsed(start, end));


		placeActController = new Field::Actor::PlaceActorController(level);


		start = ProfilerCPU::GetCounter();
		infoController = new InfoController(level);
		end = ProfilerCPU::GetCounter();

		Debug::Log("Create InfoController : %f", ProfilerCPU::CalcElapsed(start, end));

		auto onDepartPassenger = std::bind(&Actor::PlaceActorController::DepartPassenger, placeActController, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		placeContainer->SetDepartPassengerFanctor(onDepartPassenger);

		auto onStartMorph = std::bind(&Actor::PlaceActorController::OnStartMorphing, placeActController, std::placeholders::_1, std::placeholders::_2);
		placeContainer->SetMorphingFantor(onStartMorph);

		onChangePlaceType = std::bind(&Actor::PlaceActorController::ChangeActor, placeActController, std::placeholders::_1);

		routeProcessor = new Model::RouteProcessor(onChangePlaceType);
	}

	/**************************************
	クリア処理
	***************************************/
	void FieldController::Clear()
	{
		//フィールドレベルに関係ないものをリセット
		cursor->Reset();
		operateContainer->Clear();
		placeContainer->Clear();
		routeContainer.clear();

		//フィールドレベルが関係するインスタンスを削除
		SAFE_DELETE(skybox);
		SAFE_DELETE(placeActController);
		SAFE_DELETE(infoController);
		SAFE_DELETE(routeProcessor);

		//パラメータリセット
		cntFrame = 0;
		developmentLevelAI = 0.0f;
		developSpeedBonus = 1.0f;
		enableDevelop = true;
		flgWaitPopup = false;

		//ステートをIdleへ変更
		current = State::Idle;
		state = fsm[current];
	}

	/**************************************
	CSV読み込み処理
	TODO：読み込むデータを選択できるようにする
	***************************************/
	void FieldController::Load()
	{
		LARGE_INTEGER start, end;

		//アクターのデータ読み込み
		placeActController->Load();

		//モデルのデータ読み込み
		start = ProfilerCPU::GetCounter();
		placeContainer->LoadCSV(Const::FieldDataFile[currentLevel]);
		end = ProfilerCPU::GetCounter();

		Debug::Log("Load ModelData : %f", ProfilerCPU::CalcElapsed(start, end));

		//アクター生成
		start = ProfilerCPU::GetCounter();
		auto places = placeContainer->GetAllPlaces();
		for (auto&& place : places)
		{
			placeActController->SetActor(place);
		}
		end = ProfilerCPU::GetCounter();

		Debug::Log("Create Actor : %f", ProfilerCPU::CalcElapsed(start, end));

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
		//param.levelAI = (int)developmentLevelAI;
		//param.ratioLevel = (float)developmentLevelAI / MaxDevelopmentLevelAI;
#if _DEBUG
		Debug::Begin("DebugTool");
		if (Debug::Button("AILevel 9999"))
			developmentLevelAI = 9999.0f;
		Debug::End();
#endif

		param.levelAI = (int)developmentLevelAI;
		param.ratioLevel = (float)developmentLevelAI / MaxDevelopmentLevelAI;
		param.currentFieldLevel = (int)currentLevel;
		developper->EmbedViewerParam(param);
	}

	/**************************************
	道作成時のコールバック設定処理
	***************************************/
	void FieldController::SetCallbackBuildRoad(const std::function<void(std::vector<Model::PlaceModel*>&)>& callback)
	{
		onBuildRoad = callback;
	}

	/**************************************
	レベルアップするかどうかの判定
	***************************************/
	bool FieldController::ShouldLevelUp()
	{
		//宇宙レベルではレベルアップしない
		if (currentLevel == FieldLevel::Space)
			return false;

		//AI発展レベルが最大値に到達していたらレベルアップする
		return developmentLevelAI >= MaxDevelopmentLevelAI;
	}

	/**************************************
	カメラを切り替えるかどうかの判定
	***************************************/
	bool FieldController::ShouldSwicthCamera() const
	{
		return input->CheckSwicthCameraMode();
	}

	/**************************************
	カメラを回転させるかどうかの判定
	***************************************/
	bool FieldController::ShouldRotateCamera() const
	{
		return input->CheckRotateCamera();
	}

	/*************************************
	ポップアップを待機するかどうか
	***************************************/
	bool FieldController::ShouldWaitPopup() const
	{
		return flgWaitPopup;
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
			SetLinkLevelInfo();
		};

		//単体リンクレベル調整ファンクタ
		handler.functerInt[Handler::FuncterID_int::AdjustLink] = [&](int num)
		{
			placeContainer->AddLinkLevel(num);
			SetLinkLevelInfo();
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
			placeContainer->CreateTown(place);
			placeActController->CreateNewTown(place);
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
			enableDevelop = !isSeal;
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

		//アトランティス作成地の取得
		auto getAtlantis = std::bind(&FieldController::GetAtlantisPlace, this);
		handler.functerPlaceReturn[Handler::FuncterID_PlaceReturn::Atlantis] = getAtlantis;

		//アトランティス出現
		handler.functerPlace[Handler::FuncterID_Place::SetAtlantis] = [&](auto place)
		{
			std::vector<const Model::PlaceModel*> container = placeContainer->CreateAtlantis(place);
			placeActController->SetAtlantis(place, container);
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
		float bonusSideWay = placeActController->GetSideWayBonus();

		//宇宙レベルでは最大値をとりあえず増やしてしまう
		float MaxLevel = currentLevel == FieldLevel::Space ? MaxDevelopmentLevelAI * 1000.0f : MaxDevelopmentLevelAI;

		developmentLevelAI = Math::Clamp(0.0f, MaxLevel, developmentLevelAI + raiseValue + bonusSideWay);

		// リワードに反映
		if (currentLevel == FieldLevel::Space)
		{
			RewardController::Instance()->SetRewardData(RC::Type::MasterAI, (int)(developmentLevelAI));
		}
	}

	/**************************************
	街が繋がった
	***************************************/
	void FieldController::OnConnectedTown(const Model::PlaceModel * town, const Model::PlaceModel * gate)
	{
		placeContainer->OnConnectedTown(town, gate);
		placeActController->OnConnectedTown(town);
	}

	/**************************************
	アトランティス予定地取得
	***************************************/
	const Model::PlaceModel * FieldController::GetAtlantisPlace()
	{
		std::vector<Model::PlaceModel*> ignoreList;

		while (true)
		{
			const Model::PlaceModel* target = placeContainer->GetNonePlace();

			if (placeActController->EnableAtlantis(target->GetPosition()))
				return target;

			ignoreList.push_back(const_cast<Model::PlaceModel*>(target));
		}

		return nullptr;
	}

	/**************************************
	リンクレベル情報をInfoControllerにセットする
	***************************************/
	void FieldController::SetLinkLevelInfo()
	{
		auto infoLinkLevel = placeContainer->GetAllTownLevel();
		infoController->SetAllLinkLevel(infoLinkLevel);
	}

	/**************************************
	操作説明のセット
	***************************************/
	void FieldController::SetOperationExplanation()
	{
		viewer->SetOperationExplanation(
			(OperationExplanationViewer::OperationID)operationZ,
			(OperationExplanationViewer::OperationID)operationX,
			(OperationExplanationViewer::OperationID)operationSpace
		);
	}

	/**************************************
	UI描画の可否判定セット
	***************************************/
	void FieldController::SetViewerActive(bool flag)
	{
		isViewerActive = flag;
	}

	/**************************************
	スコアの取得
	***************************************/
	int FieldController::GetScore(FieldLevel current)
	{
		return score->GetScore(current);
	}

	/**************************************
	スコアのセット
	***************************************/
	void FieldController::SetScore()
	{
		score->SetScore((int)developmentLevelAI, currentLevel);
	}
}