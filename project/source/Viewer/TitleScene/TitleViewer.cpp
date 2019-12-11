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
#include "../../../Framework/Input/input.h"
#include "../../Scene/GameScene.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

//=====================================
// コンストラクタ
//=====================================
TitleViewer::TitleViewer()
{
	logo = new TitleLogo();
	selectViewer = new SelectViewer();
}

//=====================================
// デストラクタ
//=====================================
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(logo);
	SAFE_DELETE(selectViewer);
}

//=====================================
// 更新
//=====================================
void TitleViewer::Update()
{
	logo->Update();
	selectViewer->Update();
}

//=====================================
// 描画
//=====================================
void TitleViewer::Draw()
{
	if (!isActive)
		return;

	logo->Draw();

	// 別ウインドウを作成するので最後
	selectViewer->Draw();
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
	return Keyboard::GetTrigger(DIK_RETURN);
}

//=====================================
// 次のシーンを指定する
//=====================================
void TitleViewer::SetNextScene(GameScene& entity)
{
	if (selectViewer->CheckNextScene() == 0)
	{
		PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::Title, 0.1f, 30, true);
		PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::City, 0.1f, 30);
		entity.ChangeState(GameScene::State::Idle);
	}
	else if (selectViewer->CheckNextScene() == 1)
	{
		// トロフィー確認
	}
	else if (selectViewer->CheckNextScene() == 2)
	{
		// ゲーム終了
		PostQuitMessage(0);
	}
}
