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
class BaseViewer;
class ItemStockViewer;
class TimerViewer;
class LevelViewer;
class GradeUpViewer;
class GradeFrameViewer;
class GradeNameViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GameViewer
{
public:
	enum ViewerNo
	{
		ItemStock,
		Timer,
		Level,
		GradeUp,
		GradeFrame,
		GradeName,
		Max,
	};

	GameViewer();
	~GameViewer();

	void Update(void);
	void Draw(void);

	//パラメータ受け取り
	void ReceiveParam(GameViewerParam&param);

	void SetActive(bool flag);
	void SetActive(bool flag, ViewerNo viewer);

	void SetGradeUp(std::function<void(void)> Callback = nullptr);

	std::vector <BaseViewer*> gameViewer;

private:
	ItemStockViewer *stockViewer;
	TimerViewer *timerViewer;
	LevelViewer *levelViewer;
	GradeUpViewer *gradeUpViewer;
	GradeFrameViewer *gradeFrameViewer;
	GradeNameViewer *gradeNameViewer;

	bool isActive;
};

#endif

