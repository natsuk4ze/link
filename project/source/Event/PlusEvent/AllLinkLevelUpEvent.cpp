//=============================================================================
//
// 町全体リンクレベル上昇イベントクラス [AllLinkLevelUpEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "AllLinkLevelUpEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int LinkLevelUpNum = 1;
const std::string AllLinkLevelUpEvent::CityMessage[] = {
	{"台風の被害なし！\n作物の収穫量が200%に！！"},
	{"品種改良に成功！\n増殖する稲「無玄米」が誕生！"},
	{"畑に適した土壌を発見！\n収穫量が倍増！"}
};
const std::string AllLinkLevelUpEvent::WorldMessage[] = {
	{"オリンピックが開催された！\n各地で新しいヒーローの誕生だ！"},
	{"水泳選手による名言誕生！\n「マジ気持ちいい」"},
	{"選手たちが金メダルを獲得！\n国の活気上昇！！"}
};
const std::string AllLinkLevelUpEvent::SpaceMessage[] = {
	{"めっちゃ映えする宇宙食が開発されてハッピー！"},
	{"新惑星の新食材で新宇宙食ができた！新感覚！！"},
	{"ミシュラン公認！？\n三ツ星宇宙食専門レストラン誕生！！"}
};

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
AllLinkLevelUpEvent::AllLinkLevelUpEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetData("全ての町のリンクレベルが上昇",
		GuideActor::AnimState::FistPump,
		SoundConfig::AllLinkLevelUp);
}

//=============================================================================
// デストラクタ
//=============================================================================
AllLinkLevelUpEvent::~AllLinkLevelUpEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void AllLinkLevelUpEvent::Update()
{
	fieldEventHandler->AdjustAllLinkLevel(LinkLevelUpNum);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void AllLinkLevelUpEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string AllLinkLevelUpEvent::GetEventMessage(int FieldLevel)
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
