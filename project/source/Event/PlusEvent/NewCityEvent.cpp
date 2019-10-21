//=============================================================================
//
// 新しい町イベントクラス [NewCityEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "NewCityEvent.h"

#include "../../../Framework/Camera/CameraTranslationPlugin.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
NewCityEvent::NewCityEvent(EventViewer *Ptr) : eventViewer(Ptr)
{
	NewTown = fieldEventHandler->GetNewTownPosition();
	const D3DXVECTOR3 TownPosVec3 = NewTown->GetPosition().ConvertToWorldPosition();
	fieldEventHandler->PauseGame();

	eventViewer->SetEventTelop(PositiveEvent01, [=]()
	{
		Camera::TranslationPlugin::Instance()->Move(
			TownPosVec3,
			30,
			[&]() {fieldEventHandler->CreateNewTown(NewTown); });
	});
}

//=============================================================================
// デストラクタ
//=============================================================================
NewCityEvent::~NewCityEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void NewCityEvent::Update()
{
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void NewCityEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string NewCityEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("ようこそジャパリパークへ");
	}
	else if (FieldLevel == Field::Model::World)
	{

	}
	else if (FieldLevel == Field::Model::Space)
	{

	}

	if (!MessageContainer.empty())
	{
		int MessageNo = rand() % MessageContainer.size();
		return MessageContainer.at(MessageNo);
	}
	else
	{
		string ErrMsg = "イベントメッセージがありません";
		return ErrMsg;
	}
}
