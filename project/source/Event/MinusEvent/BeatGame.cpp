//=============================================================================
//
// 連打ゲームイベントクラス [BeatGame.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "BeatGame.h"
#include <mutex>
#include <iostream>
#include "../../Viewer/GameScene/Controller/BeatGameViewer.h"
#include "../../../Framework/Input/input.h"
#include "../../Reward/RewardController.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../../Framework/Task/TaskManager.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************

//連打の回数
static const int goalInput = 20;

//準備時間
static const float readyTime = 3.0f;

//ゲーム時間
static const float gameTime = 5.0f;

//=============================================================================
// コンストラクタ
//=============================================================================
BeatGame::BeatGame(BeatGame::GameType type,
	BeatGameViewer *viewer,
	std::function<void(bool)> OnFinishTelop,
	std::function<void(bool)> onFinishEvent) :
	EventBase(false),
	TelopOver(false),
	isSuccess(false),
	isReady(false),
	isFinished(false),
	canSetReady(true),
	canSetGo(true),
	countInput(0),
	countFrame(0),
	OnFinishTelop(OnFinishTelop),
	beatGameViewer(viewer),
	onFinishBeat(onFinishEvent)
{
	//再生中のイベントをセット
	playingEvent = type;

	//ゲームタイトルをセット
	beatGameViewer->SetGameTitle(GetGameTitle());

	//パラメータを初期値にセット
	beatGameViewer->SetGameGauge(1.0f);
	beatGameViewer->SetRemainTime(gameTime);

	//ビューワは最初は非表示
	beatGameViewer->SetActive(false);

	SE::Play(SoundConfig::SEID::TimeStopEventHappen, 1.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
BeatGame::~BeatGame()
{

}

//=============================================================================
// 更新
//=============================================================================
void BeatGame::Update()
{
	// テロップ再生中またゲーム終了
	if (!TelopOver || !UseFlag) return;

	if (!isReady)
	{
		//レディーテキストをセット
		SetReadyText();

		//フレームカウント更新
		countFrame++;

		//準備時間に達したら
		if (countFrame / 30.0f >= readyTime)
		{
			//フレームカウントリセット
			countFrame = 0;

			//準備完了状態に移行
			isReady = true;

			SE::Play(SoundConfig::SEID::BeatStart, 1.0f);
		}
	}
	else
	{
		//ゴーテキストをセット
		SetGoText();

		//フレームカウント更新
		countFrame++;

		//入力カウントを更新(*注意：本番はどのキー入力でもOKにする？)
		if(IsExistInput())
		{
			if (!isFinished)
			{
				SE::Play(SoundConfig::SEID::Beat, 1.0f);
			}
			countInput++;
		}

		//ビュアーのパラメータをセット
		SetViewerParam();

		//成功したか判定
		if (IsSuccess())
		{
			//結果を通知
			if (onFinishBeat != nullptr)
			{
				onFinishBeat(true);
			}

			//成功リザルトを表示
			beatGameViewer->SetResult(BeatResultViewer::Success, [&]() {EventOver(); });

			// リワードに反映
			RewardController::Instance()->SetRewardData(RC::Type::ButtonMashing, 1);

			//成功
			isSuccess = true;

			//終了
			isFinished = true;

			SE::Play(SoundConfig::SEID::BeatFinish, 1.0f);
			TaskManager::Instance()->CreateDelayedTask(60, [&]()
			{
				SE::Play(SoundConfig::SEID::BeatSuccess, 1.0f);
			});
		}

		//失敗したか判定
		if (IsFailed())
		{
			//結果を通知
			if (onFinishBeat != nullptr)
			{
				onFinishBeat(false);
			}

			//失敗リザルトを表示
			beatGameViewer->SetResult(BeatResultViewer::Failed, [&]() {EventOver(); });

			//失敗
			isSuccess = false;

			//終了
			isFinished = true;

			SE::Play(SoundConfig::SEID::BeatFinish, 1.0f);
			TaskManager::Instance()->CreateDelayedTask(60, [&]()
			{
				SE::Play(SoundConfig::SEID::BeatFailed, 1.0f);
			});
		}
	}
	beatGameViewer->Update();
}

//=============================================================================
// 描画
//=============================================================================
void BeatGame::Draw()
{
	if (!UseFlag)
		return;

	if (!TelopOver) return;

	beatGameViewer->Draw();
}

//=============================================================================
// レディーテキストセット処理(一度だけ実行)
//=============================================================================
void BeatGame::SetReadyText(void)
{
	if (!canSetReady) return;

	SE::Stop(SoundConfig::SEID::AIBurstSE);
	SE::Play(SoundConfig::SEID::Ready, SoundConfig::VolumeVoice);
	beatGameViewer->SetReady();
	canSetReady = false;
}

//=============================================================================
// ゴーテキストセット処理(一度だけ実行)
//=============================================================================
void BeatGame::SetGoText(void)
{
	if (!canSetGo) return;

	beatGameViewer->SetGo();
	canSetGo = false;
}

//=============================================================================
// ビュアーパラメータのセット処理
//=============================================================================
void BeatGame::SetViewerParam(void)
{
	if (isFinished) return;

	float remainTime = gameTime - countFrame / 30.0f;
	float gaugeRatio = 1.0f - (float)((float)countInput / (float)goalInput);

	beatGameViewer->SetRemainTime(remainTime);
	beatGameViewer->SetGameGauge(gaugeRatio);
}

//=============================================================================
// 連打ゲームタイトル取得処理
//=============================================================================
BeatTitleViewer::TitleID BeatGame::GetGameTitle(void)
{
	BeatTitleViewer::TitleID id;

	//id振り分け
	switch (playingEvent)
	{
	case BeatGame::AILevelDecrease:
		id = BeatTitleViewer::CalmAI;
		break;

	case BeatGame::BanStockUse:
		id = BeatTitleViewer::CalmAI;
		break;

	case BeatGame::CityDestroyEvent:
		id = BeatTitleViewer::ProtectCity;
		break;

	default:
		break;
	}

	return id;
}

//=============================================================================
// 入力があるかどうか
//=============================================================================
bool BeatGame::IsExistInput() const
{
	if (isFinished)
		return false;

	//キーボードからの入力
	if (Keyboard::GetTrigger(DIK_C))
		return true;

	//ゲームパッドからの入力
	if (GamePad::GetTrigger(0, BUTTON_A) || GamePad::GetTrigger(0, BUTTON_C) || GamePad::GetTrigger(0, BUTTON_X))
		return true;

	return false;
}

//=============================================================================
// 成功したか判定処理
//=============================================================================
bool BeatGame::IsSuccess(void)
{
	if (isFinished) return false;

	return 	countInput >= goalInput;
}

//=============================================================================
// 失敗したか判定処理
//=============================================================================
bool BeatGame::IsFailed(void)
{
	if (isFinished) return false;

	return countFrame >= gameTime * 30;
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string BeatGame::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// カウントダウン開始
//=============================================================================
void BeatGame::CountdownStart(void)
{
	TelopOver = true;
	beatGameViewer->SetActive(true);
}

//=============================================================================
// イベント終了
//=============================================================================
void BeatGame::EventOver(void)
{
	OnFinishTelop(isSuccess);
	UseFlag = false;
	beatGameViewer->SetActive(false);
}