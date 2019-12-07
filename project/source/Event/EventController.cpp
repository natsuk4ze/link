//=============================================================================
//
// イベントコントローラークラス [EventController.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "EventController.h"
#include "EventConfig.h"
#include "PlusEvent/AILevelUpEvent.h"
#include "PlusEvent/AllLinkLevelUpEvent.h"
#include "PlusEvent/TimeRecoveryEvent.h"
#include "PlusEvent/LinkLevelUpEvent.h"
#include "PlusEvent/FamousPeopleEvent.h"
#include "PlusEvent/CreateNewTown/NewTownEventCtrl.h"
#include "PlusEvent/StockRecoveryEvent.h"
#include "MinusEvent/AILevelDecreaseEvent.h"
#include "MinusEvent/BanStockUseEvent.h"
#include "MinusEvent/CityDestroyEvent.h"
#include "MinusEvent/LinkLevelDecreaseEvent.h"
#include "MinusEvent/BeatGame.h"

#include "../../Framework/Core/Utility.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../Framework/Camera/CameraShakePlugin.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Particle/BaseEmitter.h"
#include "../../Framework/Network/UDPClient.h"

#include "../Field/Place/FieldPlaceModel.h"
#include "../Viewer/GameScene/Controller/EventViewer.h"
#include "../Viewer/GameScene/ParameterContainer/EventViewerParam.h"
#include "../Viewer/GameScene/Controller/BeatGameViewer.h"
#include "../Effect/GameParticleManager.h"

#include "../Field/Camera/EventCamera.h"
#include "../Reward/RewardController.h"

#include <fstream>

#if _DEBUG
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"
#include "../../Framework/Input/input.h"
#endif

using namespace EventConfig;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const char* EventCSVPath_City = "data/FIELD/City/City_Event.csv";
const char* EventCSVPath_World = "data/FIELD/World/World_Event.csv";
const char* EventCSVPath_Space = "data/FIELD/Space/Space_Event.csv";


//=============================================================================
// コンストラクタ
//=============================================================================
EventController::EventController(int FieldLevel)
{
	eventViewer = new EventViewer();

	camera = new EventCamera();

	beatViewer = new BeatGameViewer();

	Init(FieldLevel);

	camera->AddPlugin(CameraShakePlugin::Instance());

#if _DEBUG
	ResourceManager::Instance()->MakePolygon("Event", "data/TEXTURE/PlaceTest/Event.png", { 4.5f, 4.5f }, { 13.0f,1.0f });
	polygon = new BoardPolygon();
	polygon->SetTexDiv({ 13.0f, 1.0f });
	ResourceManager::Instance()->GetPolygon("Event", polygon);
#endif
}

//=============================================================================
// デストラクタ
//=============================================================================
EventController::~EventController()
{
	Uninit();

	SAFE_DELETE(eventViewer);

	SAFE_DELETE(camera);

	SAFE_DELETE(beatViewer);

#if _DEBUG
	SAFE_DELETE(polygon);
#endif
}

//=============================================================================
// 初期化
//=============================================================================
void EventController::Init(int FieldLevel)
{
	// エミッターコンテナのクリア
	for (auto&& pair : infoEmitterContainer)
	{
		if (pair.second != nullptr)
			pair.second->SetActive(false);
	}
	infoEmitterContainer.clear();

	// CSVファイルを読み取る
	if (FieldLevel == Field::City)
	{
		LoadCSV(EventCSVPath_City);
	}
	else if (FieldLevel == Field::World)
	{
		LoadCSV(EventCSVPath_World);
	}
	else if (FieldLevel == Field::Space)
	{
		LoadCSV(EventCSVPath_Space);
	}

	beatViewer->SetFieldLevel(FieldLevel);
}

//=============================================================================
// 終了
//=============================================================================
void EventController::Uninit(void)
{
	// イベントベクトル削除
	Utility::DeleteContainer(EventVec);
	EventCSVData.clear();

	for (auto&& emitter : infoEmitterContainer)
	{
		if (emitter.second != nullptr)
			emitter.second->SetActive(false);
	}
	infoEmitterContainer.clear();
}

//=============================================================================
// 更新
//=============================================================================
void EventController::Update()
{
#if _DEBUG
	if (Keyboard::GetTrigger(DIK_F))
	{
		//EventVec.push_back(new NewTownEventCtrl(eventViewer, Field::Space, camera));
	}
#endif

	for (auto &Event : EventVec)
	{
		if (Event->GetUse())
		{
			if (Event->GetIsPauseEvent() && !Event->GetInitialized() && !InPauseEvent)
			{
				Event->Init();
			}
			else
			{
				Event->Update();
			}
		}
		else
		{
			// 使用完了のイベントを削除
			SAFE_DELETE(Event);
		}
	}

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), [&](EventBase *Event)
	{
		return Event == nullptr ? true : false;
	}), std::end(EventVec));

	//イベントカメラ更新
	camera->Update();
}

//=============================================================================
// イベントビューワ更新
//=============================================================================
void EventController::UpdateViewer(void)
{
	// イベントビューア更新
	eventViewer->Update();
}

//=============================================================================
// イベントオブジェクト描画
//=============================================================================
void EventController::DrawEventObject()
{
	// イベントオブジェクト描画
	for (auto &Event : EventVec)
	{
		Event->Draw();
	}

#if _DEBUG
	// イベントマスの可視化描画
	DrawDebug();
#endif
}

//=============================================================================
// イベントビューア描画
//=============================================================================
void EventController::DrawEventViewer()
{
	//ビートビューア描画
	beatViewer->Draw();

	// イベントビューア描画
	eventViewer->Draw();
}

#if _DEBUG
//=============================================================================
// イベントマスの可視化描画
//=============================================================================
void EventController::DrawDebug()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (auto& Object : EventCSVData)
	{
		// テスト描画
		Transform transform = Transform(
			Object.Pos.ConvertToWorldPosition() + Vector3::Up,
			{ D3DXToRadian(90.0f), 0.0f, 0.0f },
			Vector3::One);

		polygon->SetTextureIndex(Object.EventType);
		polygon->Draw(transform.GetMatrix());
	}

	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
#endif

//=============================================================================
// CSVの読み込む
//=============================================================================
void EventController::LoadCSV(const char* FilePath)
{
	//CSVファイルを読み込み
	std::ifstream stream(FilePath);

	std::string line;			// CSVを1行ずつ読むバッファ
	const char Delim = ',';		// 区切り文字
	int x = 0;					// EventのX位置
	int z = 0;					// EventのZ位置

	//CSVの終わりまで読み込み続ける
	while (std::getline(stream, line))
	{
		//1行分読み込んだデータを区切り文字で分割する
		std::vector<std::string> subStr;
		String::Split(subStr, line, Delim);

		x = 0;

		for (auto &str : subStr)
		{
			int Type = std::stoi(str);
			if (Type != EventConfig::NoEvent)
			{
				Field::FieldPosition Pos = { x, z };
				EventCSVData.push_back(EventInfo{ Pos, Type });
				infoEmitterContainer[Pos] = GameParticleManager::Instance()->Generate(GameParticle::EventInfo, Pos.ConvertToWorldPosition());
			}
			x++;
		}
		z++;
	}
}

//=============================================================================
// イベント発生の確認
//=============================================================================
bool EventController::CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& RoutePtr, int FieldLevel)
{
	bool flgPause = false;

	for (auto &place : RoutePtr)
	{
		Field::FieldPosition PlacePos = place->GetPosition();
		for (auto EventPlace = EventCSVData.begin(); EventPlace != EventCSVData.end();)
		{
			if (PlacePos.x == EventPlace->Pos.x && PlacePos.z == EventPlace->Pos.z)
			{
				CameraTranslationPlugin* Test = CameraTranslationPlugin::Instance();
				EventBase* Ptr = nullptr;

				// イベントインスタンス作成
				switch (EventPlace->EventType)
				{
				case LinkLevelUp:
					Ptr = new LinkLevelUpEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, LinkLevelUp);
					break;
				case NewCity:
					Ptr = new NewTownEventCtrl(eventViewer, FieldLevel, camera);
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, NewCity);
					flgPause = true;
					break;
				case StockRecovery:
					Ptr = new StockRecoveryEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, StockRecovery);
					break;
				case FamousPeople:
					Ptr = new FamousPeopleEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, FamousPeople);
					break;
				case AllLinkLevelUp:
					Ptr = new AllLinkLevelUpEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, AllLinkLevelUp);
					break;
				case AILevelUp:
					Ptr = new AILevelUpEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, AILevelUp);
					break;
				case TimeRecovery:
					Ptr = new TimeRecoveryEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, TimeRecovery);
					break;
				case LinkLevelDecrease:
					Ptr = new LinkLevelDecreaseEvent();
					RewardController::Instance()->SetRewardData(RC::Type::MinusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::MinusComplete, LinkLevelDecrease - 7);
					break;
				case CityDestroy:
					Ptr = new CityDestroyEvent(eventViewer, beatViewer, camera);
					RewardController::Instance()->SetRewardData(RC::Type::MinusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::MinusComplete, CityDestroy - 7);
					flgPause = true;
					break;
				case AILevelDecrease:
					Ptr = new AILevelDecreaseEvent(eventViewer, camera, beatViewer);
					RewardController::Instance()->SetRewardData(RC::Type::MinusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::MinusComplete, AILevelDecrease - 7);
					flgPause = true;
					break;
				case BanStockUse:
					if (InBanStock)
					{
						// 今ストック使用禁止中
						++EventPlace;
						continue;
					}
					else
					{
						Ptr = new BanStockUseEvent(eventViewer,
							beatViewer,
							[&](bool Flag) {SetBanStock(Flag); },
							[&]() {return GetInPause(); });
						RewardController::Instance()->SetRewardData(RC::Type::MinusMaster, 1);
						RewardController::Instance()->SetRewardData(RC::Type::MinusComplete, BanStockUse - 7);
						flgPause = true;
					}
					break;
				default:
					break;
				}

				if (Ptr != nullptr)
				{
					// イベントメッセージ設置
					eventViewer->SetEventMessage(Ptr->GetEventMessage(FieldLevel));

					// イベント中継パケットを送信
					if (flgPause)
					{
						UDPClient::SendEventPacket(EventPlace->EventType, FieldLevel);
					}

					// イベントベクトルにプッシュ
					EventVec.push_back(Ptr);
				}

				// CSVデータから発生したイベントの資料を削除
				EventPlace = EventCSVData.erase(EventPlace);

				//イベントインフォのエミッタを停止z
				infoEmitterContainer[PlacePos]->SetActive(false);
				infoEmitterContainer.erase(PlacePos);
			}
			else
				++EventPlace;
		}
	}

	return flgPause;
}

//=============================================================================
// FieldEventHandlerのポインタを受け取る
//=============================================================================
void EventController::ReceiveFieldEventHandler(FieldEventHandler *Ptr)
{
	// FieldEventHandlerのある関数を設定する
	Ptr->SetEventControllerInPause = [&](bool Flag)
	{
		SetInPause(Flag);
	};
	EventBase::ReceiveFieldEventHandler(Ptr);
}

//=============================================================================
// ビューワパラメータ埋め込み処理
//=============================================================================
void EventController::EmbedViewerParam(EventViewerParam& param)
{
	param.isStockSealed = this->InBanStock;
}

//=============================================================================
// ストック使用禁止の設置
//=============================================================================
void EventController::SetBanStock(bool Flag)
{
	InBanStock = Flag;
}

//=============================================================================
// 現在はタイムストップイベントが発生しているかどうか
//=============================================================================
void EventController::SetInPause(bool Flag)
{
	InPauseEvent = Flag;
}

//=============================================================================
// 現在はタイムストップイベントが発生しているかどうか
//=============================================================================
bool EventController::GetInPause(void)
{
	return InPauseEvent;
}

//=============================================================================
// イベントの確認用デバッグ
//=============================================================================
bool EventController::EventDebug(int FieldLevel)
{
	EventBase* Ptr = nullptr;
	bool flgPause = false;

	// イベントインスタンス作成
	if (Debug::Button("LinkLevel Up"))
	{
		Ptr = new LinkLevelUpEvent();
	}
	if (Debug::Button("New Town"))
	{
		Ptr = new NewTownEventCtrl(eventViewer, FieldLevel, camera);
		flgPause = true;
	}
	if (Debug::Button("Stock Recovery"))
	{
		Ptr = new StockRecoveryEvent();
	}
	if (Debug::Button("Famout people"))
	{
		Ptr = new FamousPeopleEvent();
	}
	if (Debug::Button("All LinlLevel Up"))
	{
		Ptr = new AllLinkLevelUpEvent();
	}
	if (Debug::Button("AI Level Up"))
	{
		Ptr = new AILevelUpEvent();
	}
	if (Debug::Button("Time Recovery"))
	{
		Ptr = new TimeRecoveryEvent();
	}
	if (Debug::Button("LinkLevel Decrease"))
	{
		Ptr = new LinkLevelDecreaseEvent();
	}
	if (Debug::Button("City Destroy"))
	{
		Ptr = new CityDestroyEvent(eventViewer, beatViewer, camera);
		flgPause = true;
	}
	if (Debug::Button("AI Level Decrease"))
	{
		Ptr = new AILevelDecreaseEvent(eventViewer, camera, beatViewer);
		flgPause = true;
	}
	if (Debug::Button("Ban StockUse"))
	{
		Ptr = new BanStockUseEvent(eventViewer,
			beatViewer,
			[&](bool Flag) {SetBanStock(Flag); },
			[&]() {return GetInPause(); });
		flgPause = true;
	}

	if (Ptr != nullptr)
	{
		// イベントメッセージ設置
		eventViewer->SetEventMessage(Ptr->GetEventMessage(FieldLevel));

		// イベントベクトルにプッシュ
		EventVec.push_back(Ptr);
	}

	return flgPause;
}