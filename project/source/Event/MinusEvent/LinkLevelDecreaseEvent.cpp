//=============================================================================
//
// リンクレベル減少イベントクラス [LinkLevelDecreaseEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "LinkLevelDecreaseEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int LinkLevelDecreaseNum = -1;
const std::string LinkLevelDecreaseEvent::CityMessage[] = {
	{"発注数の桁5つ間違えた！\n賞味期限明日までじゃん！"},
	{"SNSで拡散してもらわなくちゃ！"},
	{"いや！ちがうんすよ店長！"}
};
const std::string LinkLevelDecreaseEvent::WorldMessage[] = {
	{"隣の国が攻めてきた！"},
	{"争いは同じレベルのもの同士でしか\n発生しない！"},
	{"アフリカでは1分間に60秒進んでいます"}
};
const std::string LinkLevelDecreaseEvent::SpaceMessage[] = {
	{"君の...名前は！？"},
	{"拝啓ドッペルゲンガー様　敬具"},
	{"あなたは誰？中学の同級生？\n私は問う！"}
};

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
LinkLevelDecreaseEvent::LinkLevelDecreaseEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetMessage("リンクレベルが下がりました");
	GuideViewer::Instance()->ChangeAnim(GuideActor::AnimState::Surprised);
	SE::Play(SoundConfig::LinkLevelDown, SoundConfig::VolumeVoice);
}

//=============================================================================
// デストラクタ
//=============================================================================
LinkLevelDecreaseEvent::~LinkLevelDecreaseEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void LinkLevelDecreaseEvent::Update()
{
	fieldEventHandler->AdjustAllLinkLevel(LinkLevelDecreaseNum);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void LinkLevelDecreaseEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string LinkLevelDecreaseEvent::GetEventMessage(int FieldLevel)
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
