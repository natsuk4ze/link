//=====================================
//
// タイトルビュアー[TitleViewer.cpp]
// 機能：タイトル画面UI表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "TitleViewer.h"
#include "TitleLogo.h"
#include "SelectViewer.h"
#include "RewardViewer.h"
#include "../../../Framework/Input/input.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"

//=====================================
// コンストラクタ
//=====================================
TitleViewer::TitleViewer()
{
	logo = new TitleLogo();
	selectViewer = new SelectViewer();
	rewardViewer = new RewardViewer();
}

//=====================================
// デストラクタ
//=====================================
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(logo);
	SAFE_DELETE(selectViewer);
	SAFE_DELETE(rewardViewer);
}

//=====================================
// 更新
//=====================================
void TitleViewer::Update()
{
	if (!isActive)
		return;

	logo->Update();
	if (!rewardViewer->isPlaying)
	{
		selectViewer->Update();
	}
	else
	{
		rewardViewer->Update();
	}
}

//=====================================
// 描画
//=====================================
void TitleViewer::Draw()
{
	if (!isActive)
		return;

	if (!rewardViewer->isPlaying)
	{
		logo->Draw();

		// 別ウインドウを作成するので最後
		selectViewer->Draw();
	}
	else
	{
		rewardViewer->Draw();
	}
}

//=====================================
// 描画可否フラグのセット
//=====================================
void TitleViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=====================================
// 次のシーンを指定する
//=====================================
TitleViewer::MenuID TitleViewer::GetSelectedMenu()
{
	// リワードビューアが表示していなければ
	if (rewardViewer->isPlaying)
		return None;

	int next = selectViewer->CheckNextScene();

	if (next == 0)
		return StartGame;
	
	if (next == 1)
		return ViewReward;

	if (next == 2)
		return QuitGame;

	return None;
}

//=====================================
// 実績ビューアのセット
//=====================================
void TitleViewer::SetRewardViewer()
{
	rewardViewer->isPlaying = true;
}

//=====================================
// セレクトロゴの表示が"ゲーム開始"に設定する
//=====================================
void TitleViewer::InitSelectLogo(void)
{
	//selectViewer->InitSelectLogo();
}
