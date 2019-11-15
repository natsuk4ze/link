//=============================================================================
//
// 連打ゲームビュアー管理処理 [BeatGameViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_GAME_VIEWER_H_
#define _BEAT_GAME_VIEWER_H_

#include <vector>
#include <functional>
#include "../../../../Framework/Pattern/Delegate.h"
#include "BeatTitleViewer.h"
#include "BeatResultViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewer;
class BeatTitleViewer;
class BeatGaugeViewer;
class BeatTimerViewer;
class BeatStarterViewer;
class BeatResultViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatGameViewer
{
public:
	BeatGameViewer();
	~BeatGameViewer();

	void Update(void);
	void Draw(void);

	//連打ゲームのタイトルを設置する
	void SetGameTitle(BeatTitleViewer::TitleID id);

	//連打ゲームのゲージを設置する
	void SetGameGauge(float percent);

	//連打ゲームの残り時間を設定する
	void SetRemainTime(float time);

	//「Ready」を表示する
	void SetReady(void);

	//「GO」を表示する
	void SetGo(void);

	//結果を表示する
	void SetResult(BeatResultViewer::ResultID id, std::function<void(void)> Callback = nullptr);

private:
	std::vector <BaseViewer*> beatGameViewer;
	BeatTitleViewer *titleViewer;
	BeatGaugeViewer *gaugeViewer;
	BeatTimerViewer *timerViewer;
	BeatStarterViewer *starterViewer;
	BeatResultViewer *resultViewer;
};

#endif

