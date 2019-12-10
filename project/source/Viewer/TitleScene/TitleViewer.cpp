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
#include "../../Scene/GameScene.h"

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
// シーンチェンジ
//=====================================
bool TitleViewer::CheckSceneChange()
{
	return Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C);
}

//=====================================
// 次のシーンを指定する
//=====================================
void TitleViewer::SetNextScene(GameScene& entity)
{
	// リワードビューアが表示していなければ
	if (!rewardViewer->isPlaying)
	{
		if (selectViewer->CheckNextScene() == 0)
		{
			// ゲーム開始
			entity.ChangeState(GameScene::State::Idle);
		}
		else if (selectViewer->CheckNextScene() == 1)
		{
			// トロフィー確認
			rewardViewer->isPlaying = true;
		}
		else if (selectViewer->CheckNextScene() == 2)
		{
			// ゲーム終了
			PostQuitMessage(0);
		}
	}
}

//=====================================
// セレクトロゴの表示が"ゲーム開始"に設定する
//=====================================
void TitleViewer::InitSelectLogo(void)
{
	//selectViewer->InitSelectLogo();
}
