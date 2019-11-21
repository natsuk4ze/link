//=============================================================================
//
// Gameシーンビュアー管理処理 [GameViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class ItemStockViewer;
class TimerViewer;
class LevelViewer;
class BaseViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GameViewer
{
public:
	GameViewer();
	~GameViewer();

	void Update(void);
	void Draw(void);

	//パラメータ受け取り
	void ReceiveParam(GameViewerParam&param);

	void SetActive(bool flag);

	std::vector <BaseViewer*> gameViewer;

private:
	ItemStockViewer *stockViewer;
	TimerViewer *timerViewer;
	LevelViewer *levelViewer;

	bool isActive;
};

#endif

