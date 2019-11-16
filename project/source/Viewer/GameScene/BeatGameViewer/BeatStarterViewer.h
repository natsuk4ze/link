
//=============================================================================
//
// 連打ゲームスタータービュアー処理 [BeatStarterViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_STARTER_VIEWER_H_
#define _BEAT_STARTER_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatStarterViewer :public BaseViewer
{
public:
	BeatStarterViewer();
	~BeatStarterViewer();

	void Update();
	void Draw(void);
	void SetReady(void);
	void SetGo(void);

private:
	BaseViewerDrawer *readyText;
	BaseViewerDrawer *goText;

	//レディーテキストをスクリーンイン
	void InReady(void);

	//ゴーテキストを出現させる処理
	void InGo(void);

	//レディーすべきか
	bool shouldReady;

	//ゴーすべきか
	bool shouldGo;

	//フレームカウント
	int countFrame;

	//アニメーション時間
	float animTime;
};

#endif