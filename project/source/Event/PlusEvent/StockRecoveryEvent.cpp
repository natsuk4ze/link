//=============================================================================
//
// ストック回数回復イベントクラス [StockRecoveryEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "StockRecoveryEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int AddNum = 3;
const std::string StockRecoveryEvent::CityMessage[] = {
	{"祭りだワッショイ！"},
	{"タピオカ投げ祭り！\n今日はみんなでタピろう！"},
	{"射的で景品ゲット！"}
};
const std::string StockRecoveryEvent::WorldMessage[] = {
	{"裏庭から昔の金貨がザックザク！"},
	{"海水浴中に砂浜に埋められてたらなんか出てきた！"},
	{"こんなところに金隠しやがって..."}
};
const std::string StockRecoveryEvent::SpaceMessage[] = {
	{"ふと空を見上げたら星が綺麗だった"},
	{"あっ！流れ星！"},
	{"ペガサス流星拳！！"}
};

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
StockRecoveryEvent::StockRecoveryEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetData("ドリルのストックが回復",
		GuideActor::AnimState::Cheering,
		SoundConfig::StockRecovery);
}

//=============================================================================
// デストラクタ
//=============================================================================
StockRecoveryEvent::~StockRecoveryEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void StockRecoveryEvent::Update()
{
	fieldEventHandler->AddStockNum(AddNum);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void StockRecoveryEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string StockRecoveryEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	int r = rand() % 3;
	if (FieldLevel == Field::City)
	{
		MessageContainer.push_back(CityMessage[r]);
	}
	else if (FieldLevel == Field::World)
	{
		MessageContainer.push_back(WorldMessage[r]);
	}
	else if (FieldLevel == Field::Space)
	{
		MessageContainer.push_back(SpaceMessage[r]);
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
