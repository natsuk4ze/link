//*****************************************************************************
// 11/15(金)～おおはま改変
//*****************************************************************************

//=============================================================================
//
// 連打ゲームイベントクラス [BeatGame.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BeatGame_H_
#define _BeatGame_H_

#include "../../Viewer/GameScene/BeatGameViewer/BeatTitleViewer.h"
#include "../EventBase.h"
#include <functional>
#include <string>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BeatGameViewer;
class BeatTitleViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatGame : public EventBase
{
public:
	//ゲームタイトルの種類
	enum GameType
	{
		AILevelDecrease,
		BanStockUse,
		CityDestroyEvent,
	};

	BeatGame(BeatGame::GameType type, BeatGameViewer *viewer, std::function<void(bool)> CallBack = nullptr);
	~BeatGame();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void CountdownStart(void);

private:
	int countInput;
	float countFrame;
	bool TelopOver;
	bool isSuccess;
	bool isReady;
	bool isFinished;
	bool canSetReady;
	bool canSetGo;
	std::function<void(bool)> Callback;

	void EventOver(void);

	//成功したか判定処理
	bool IsSuccess(void);

	//失敗したか判定処理
	bool IsFailed(void);

	//レディーテキストセット処理
	void SetReadyText(void);

	//ゴーテキストセット処理
	void SetGoText(void);

	//ビュアーパラメータのセット処理
	void SetViewerParam(void);

	//ゲームタイトル取得処理
	BeatTitleViewer::TitleID GetGameTitle(void);

	//再生中のイベント
	GameType playingEvent;

	//連打ゲームビュアー
	BeatGameViewer *beatGameViewer;
};

#endif
