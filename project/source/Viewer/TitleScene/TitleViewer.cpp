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
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../../Framework/Task/TaskManager.h"

//=====================================
// コンストラクタ
//=====================================
TitleViewer::TitleViewer() :
	cntFrame(0), isSelect(false), isFlash(false)
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
		if (isSelect)
		{
			// 点滅処理
			cntFrame++;
			if (isFlash)
			{
				if (cntFrame % 5 == 0)
				{
					isFlash = false;
				}
			}
			else
			{
				if (cntFrame % 5 == 0)
				{
					isFlash = true;
				}
			}
			//return;
		}
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

		if (isFlash)
			return;

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
	if (isSelect)
		return false;

	if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		SE::Play(SoundConfig::SEID::Select01, 1.0f);
		isSelect = true;
		isFlash = true;
		return true;
	}
	else
	{
		return false;
	}
}

//=====================================
// 次のシーンを指定する
//=====================================
void TitleViewer::SetNextScene(GameScene& entity)
{
	// リワードビューアが表示していなければ
	if (!rewardViewer->isPlaying)
	{
		if (!isSelect)
			return;

		if (selectViewer->CheckNextScene() == 0)
		{
			// ゲーム開始
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::City, 0.1f, 30);
				entity.ChangeState(GameScene::State::Idle);
				//isActive = true;
				isSelect = false;
				isFlash = false;
				cntFrame = 0;
			});
			PlayBGM::Instance()->FadeOut();
		}
		else if (selectViewer->CheckNextScene() == 1)
		{
			// ゲーム開始
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				// トロフィー確認
				rewardViewer->isPlaying = true;
				isActive = true;
				isFlash = false;
				isSelect = false;
				cntFrame = 0;
			});
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
