
//=============================================================================
//
// リンクレベルアップビュアー処理 [LinkLevelUpViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LINK_LEVEL_UP_VIEWER_H_
#define _LINK_LEVEL_UP_VIEWER_H_

#include "../../Framework/BaseViewer.h"

#include <functional>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class LinkLevelUpViewer :public BaseViewer
{
public:
	LinkLevelUpViewer();
	~LinkLevelUpViewer();

	void Update();
	void Draw(void);
	void Set(int level, std::function<void()> callback);

private:

	//テキスト
	BaseViewerDrawer *text;

	//月桂樹
	BaseViewerDrawer *laurel;

	//数字
	CountViewerDrawer *num;

	//＋
	BaseViewerDrawer *plus;

	//コールバック
	std::function<void()> callback;

	//ビュアー再生
	void Play();

	//フェードイン
	void FadeIn();

	//フェードアウト
	void FadeOut();

	//数字出現処理
	void InNum();

	//再生中かどうか
	bool isPlaying;

	//フレームカウント
	int countFrame;

	//現在のアニメーション
	int currentAnim;

	//パラメータを受け取る箱
	int parameterBox;

	//アニメーション時間
	float animTime;
};

#endif