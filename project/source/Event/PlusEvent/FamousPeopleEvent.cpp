//=============================================================================
//
// 有名人イベントクラス [FamousPeopleEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "FamousPeopleEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ボーナス数値
const float BonusNum = 1.5f;
// デフォルトのボーナス効果フレーム
const int DefalutBonusFrame = 150;
const std::string FamousPeopleEvent::message[] = {
	{"最近ブームの芸人がうちの町にも来た！"},
	{"M-1優勝芸人がこの町の観光大使に！？"},
	{"おにぎりマン大好き好き君"}
};

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
FamousPeopleEvent::FamousPeopleEvent() :
	EventBase(false),
	RemainTime(DefalutBonusFrame)
{
	fieldEventHandler->SetDevelopBonus(BonusNum);
	GuideViewer::Instance()->SetData("一定時間発展度が上昇します",
		GuideActor::AnimState::FistPump,
		SoundConfig::DevelopSpeedUp);
}

//=============================================================================
// デストラクタ
//=============================================================================
FamousPeopleEvent::~FamousPeopleEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void FamousPeopleEvent::Update()
{
	RemainTime--;
	if (RemainTime <= 0)
	{
		// ボーナス停止処理
		fieldEventHandler->SetDevelopBonus(1.0f);

		UseFlag = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void FamousPeopleEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string FamousPeopleEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	int r = rand() % 3;
	MessageContainer.push_back(message[r]);

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
