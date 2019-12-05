//=============================================================================
//
// リンクレベル上昇イベントクラス [LinkLevelUpEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "LinkLevelUpEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int LinkLevelUpNum = 1;
const std::string LinkLevelUpEvent::message[] = {
	{"となりの町から食べ物が入ってきて大ブーム！"},
	{"原住民から新たな健康法の伝授！\n寿命が伸びるらしい..."},
	{"宇宙人発見！\n人類に新たな技術！！"}
};

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
LinkLevelUpEvent::LinkLevelUpEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetMessage("町のリンクレベルが上昇しました");
	GuideViewer::Instance()->ChangeAnim(GuideActor::AnimState::FistPump);
	SE::Play(SE::VoiceType::LinkLevelUp, 1.0);
}

//=============================================================================
// デストラクタ
//=============================================================================
LinkLevelUpEvent::~LinkLevelUpEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void LinkLevelUpEvent::Update()
{
	fieldEventHandler->AdjustAllLinkLevel(LinkLevelUpNum);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void LinkLevelUpEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string LinkLevelUpEvent::GetEventMessage(int FieldLevel)
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
