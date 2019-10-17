//=============================================================================
//
// イベントコントローラークラス [EventController.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "EventController.h"
#include "EventConfig.h"
#include "MinusEvent/CityDestroyEvent.h"


#include "../../Framework/Core/Utility.h"
#include "../../Framework/String/String.h"

#include <fstream>
#include <string>

#if _DEBUG
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"
#endif

using namespace EventConfig;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 使用していないイベントを削除
//bool RemoveCondition(EventBase *Event) { return !Event->GetUse(); }
bool RemoveCondition(EventBase *Event) { return Event == nullptr ? true : false; }

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//std::vector<Field::Model::PlaceModel*> *EventController::route = nullptr;
std::vector<EventInfo> EventController::EventCSVData;
std::vector<EventBase*> EventController::EventVec;


//=============================================================================
// コンストラクタ
//=============================================================================
EventController::EventController(int FieldLevel) : FieldLevel(FieldLevel)
{
	LoadCSV("data/FIELD/sample01_Event.csv");

#if _DEBUG
	ResourceManager::Instance()->MakePolygon("Event", "data/TEXTURE/PlaceTest/Event.png", { 4.5f, 4.5f }, { 12.0f,1.0f });
#endif
}

//=============================================================================
// デストラクタ
//=============================================================================
EventController::~EventController()
{
	// イベントベクトル削除
	Utility::DeleteContainer(EventVec);
}

//=============================================================================
// 更新
//=============================================================================
void EventController::Update()
{
	for (auto &Event : EventVec)
	{
		if (Event->GetUse())
		{
			Event->Update();
		}
		else
		{
			SAFE_DELETE(Event);
		}
	}

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), RemoveCondition), std::end(EventVec));
}

//=============================================================================
// 描画
//=============================================================================
void EventController::Draw()
{
	for (auto &Event : EventVec)
	{
		Event->Draw();
	}

#if _DEBUG
	DrawDebug();
#endif
}

#if _DEBUG
//=============================================================================
// イベントマス描画
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
			{ Object.x * 10.0f, 1.0f, Object.z * -10.0f },
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
				EventCSVData.push_back(EventInfo{ x, z, Type });
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
		Field::FieldPosition Pos = place->GetPosition();
		for (auto EventPlace = EventCSVData.begin(); EventPlace != EventCSVData.end();)
		{
			if (Pos.x == EventPlace->x && Pos.z == EventPlace->z)
			{
				switch (EventPlace->EventType)
				{
				case CityLevelUp:
					break;
				case NewCity:
					break;
				case ChipRecovery:
					break;
				case FamousPeople:
					break;
				case Bonus:
					break;
				case AILevelUp:
					break;
				case CityLevelDecrease:
					break;
				case CityDestroy:
					EventVec.push_back(new CityDestroyEvent(FieldLevel, Vector3::Zero));
					break;
				case AILevelDecrease:
					break;
				case MoveInverse:
					break;
				case BanSpecialChip:
					break;
				case CongestionUp:
					break;
				default:
					break;
				}

				EventPlace = EventCSVData.erase(EventPlace);
			}
			else
				++EventPlace;
		}
	}
}
