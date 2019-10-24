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
#include "PlusEvent/NewCityEvent.h"
#include "PlusEvent/StockRecoveryEvent.h"
#include "MinusEvent/AILevelDecreaseEvent.h"
#include "MinusEvent/BanStockUseEvent.h"
#include "MinusEvent/CityDestroyEvent.h"
#include "MinusEvent/LinkLevelDecreaseEvent.h"
#include "MinusEvent/CongestionUpEvent.h"
#include "MinusEvent/MoveInverseEvent.h"

#include "../../Framework/Core/Utility.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../Framework/Camera/CameraShakePlugin.h"

#include "../Field/Place/FieldPlaceModel.h"
//イベントビューア（おーはま追記）
#include "../Viewer/GameScene/EventViewer/EventViewer.h"

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
// 使用していないイベントを削除
bool RemoveCondition(EventBase *Event) { return Event == nullptr ? true : false; }

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
EventController::EventController(int FieldLevel) : FieldLevel(FieldLevel)
{
	LoadCSV("data/FIELD/sample01_Event.csv");

	eventViewer = new EventViewer();

#if _DEBUG
	ResourceManager::Instance()->MakePolygon("Event", "data/TEXTURE/PlaceTest/Event.png", { 4.5f, 4.5f }, { 13.0f,1.0f });
#endif
}

//=============================================================================
// デストラクタ
//=============================================================================
EventController::~EventController()
{
	// イベントベクトル削除
	Utility::DeleteContainer(EventVec);
	EventCSVData.clear();

	fieldController = nullptr;

	SAFE_DELETE(eventViewer);
}

//=============================================================================
// 更新
//=============================================================================
void EventController::Update()
{
#if _DEBUG
	if (Keyboard::GetTrigger(DIK_F))
	{
		EventVec.push_back(new CityDestroyEvent(eventViewer));
	}
#endif

	for (auto &Event : EventVec)
	{
		if (Event->GetUse())
		{
			Event->Update();
		}
		else
		{
			// 使用完了のイベントを削除
			SAFE_DELETE(Event);
		}
	}

	// イベントビューア更新
	eventViewer->Update();

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), RemoveCondition), std::end(EventVec));
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
		//テスト描画
		Transform transform = Transform(
			Object.Pos.ConvertToWorldPosition() + Vector3::Up,
			{ D3DXToRadian(90.0f), 0.0f, 0.0f },
			Vector3::One);
		transform.SetWorld();
		BoardPolygon *polygon;
		ResourceManager::Instance()->GetPolygon("Event", polygon);
		polygon->SetTextureIndex(Object.EventType);
		polygon->Draw();
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
	//初期化済みであればリターン
	//if (initialized)
	//	return;

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
			}
			x++;
		}
		z++;
	}

	//初期化完了
	//initialized = true;
}

//=============================================================================
// イベント発生の確認
//=============================================================================
void EventController::CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& RoutePtr, int FieldLevel)
{
	for (auto &place : RoutePtr)
	{
		Field::FieldPosition PlacePos = place->GetPosition();
		for (auto EventPlace = EventCSVData.begin(); EventPlace != EventCSVData.end();)
		{
			if (PlacePos.x == EventPlace->Pos.x && PlacePos.z == EventPlace->Pos.z)
			{
				Camera::TranslationPlugin* Test = Camera::TranslationPlugin::Instance();
				EventBase* Ptr = nullptr;

				// イベントインスタンス作成
				switch (EventPlace->EventType)
				{
				case LinkLevelUp:
					Ptr = new LinkLevelUpEvent();
					break;
				case NewCity:
					Ptr = new NewCityEvent(eventViewer);
					break;
				case StockRecovery:
					Ptr = new StockRecoveryEvent();
					break;
				case FamousPeople:
					Ptr = new FamousPeopleEvent(150);
					break;
				case AllLinkLevelUp:
					Ptr = new AllLinkLevelUpEvent();
					break;
				case AILevelUp:
					Ptr = new AILevelUpEvent();
					break;
				case TimeRecovery:
					Ptr = new TimeRecoveryEvent();
					break;
				case LinkLevelDecrease:
					Ptr = new LinkLevelDecreaseEvent();
					break;
				case CityDestroy:
					Ptr = new CityDestroyEvent(eventViewer);
					break;
				case AILevelDecrease:
					Ptr = new AILevelDecreaseEvent();
					break;
				case MoveInverse:
					Ptr = new MoveInverseEvent(300);
					break;
				case BanStockUse:
					Ptr = new BanStockUseEvent(300);
					break;
				case CongestionUp:
					Ptr = new CongestionUpEvent(300);
					break;
				default:
					break;
				}

				if (Ptr != nullptr)
				{
					// イベントメッセージ設置
					eventViewer->SetEventMessage(Ptr->GetEventMessage(FieldLevel));

					// イベントベクトルにプッシュ
					EventVec.push_back(Ptr);

					// CSVデータから発生したイベントの資料を削除
					EventPlace = EventCSVData.erase(EventPlace);
				}
			}
			else
				++EventPlace;
		}
	}
}

//=============================================================================
// FieldControllerのポインタを受け取る
//=============================================================================
void EventController::ReceiveFieldEventHandler(FieldEventHandler *Ptr)
{
	EventBase::ReceiveFieldEventHandler(Ptr);
}