//=====================================
//
// RewardNotifierクラス[RewardNotifier.cpp]
// 機能：ゲーム内リワード達成を通知するクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "RewardNotifier.h"
#include "RewardController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "AchieveViewer.h"
#include "../Viewer/GameScene/GuideViewer/GuideViewer.h"

//=====================================
// コンストラクタ
//=====================================
RewardNotifier::RewardNotifier() :
	achieved()
{
	achieveViewer = new AchieveViewer();
}

//=====================================
// デストラクタ
//=====================================
RewardNotifier::~RewardNotifier()
{
	SAFE_DELETE(achieveViewer);
}

//=====================================
// 更新
//=====================================
void RewardNotifier::Update()
{
	CheckAchieved();
	achieveViewer->Update();
}

//=====================================
// 描画
//=====================================
void RewardNotifier::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	achieveViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// リワード到達確認
//=====================================
void RewardNotifier::CheckAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		// 既に表示していたらリターン
		if (achieved[i])
			continue;

		if (RewardController::Instance()->IsAchieved(RC::Type(i)))
		{
			GuideViewer::Instance()->SetData("実績を解除しました",
				GuideActor::AnimState::TalkingTypeB,
				SoundConfig::SEID(i + (int)SoundConfig::SEID::ButtonMashing));
			SE::Play(SoundConfig::SEID::Achieve, 1.0f);

			achieved[i] = true;
			achieveViewer->SetIndex(i);
			achieveViewer->SetActive();
		}
	}
}

//=====================================
// リワード到達確認のリセット
//=====================================
void RewardNotifier::ResetAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		achieved[RC::Type(i)] = false;
	}
}

