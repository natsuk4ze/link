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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 使用していないイベントを削除
//bool RemoveCondition(EventBase *Event) { return !Event->GetUse(); }
bool RemoveCondition(EventBase *Event) { return Event == NULL ? true : false; }

//*****************************************************************************
// グローバル変数
//*****************************************************************************



//=============================================================================
// コンストラクタ
//=============================================================================
EventController::EventController(int FieldLevel) : FieldLevel(FieldLevel)
{
	//LoadCSV("data/FIELD/sample01_Event.csv");

	EventVec.push_back(new CityDestroyEvent(FieldLevel, D3DXVECTOR3(150.0f, 0.0f, 150.0f)));

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
}

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
			// 
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
void EventController::ReceiveEvent(void)
{

}
