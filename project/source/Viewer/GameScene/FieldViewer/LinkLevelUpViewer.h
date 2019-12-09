
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
class ViewerAnimater;

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

	enum AnimLayer
	{
		Text,
		BG,
		Max
	};

	BaseViewerDrawer *text;
	BaseViewerDrawer *laurel;
	CountViewerDrawer *num;
	BaseViewerDrawer *plus;
	ViewerAnimater *anim[AnimLayer::Max];

	//コールバック
	std::function<void()> Callback;

	void AppearBG(void);
	void DisAppearBG(void);
	void SetNumPos(int level);

	//パラメータを受け取る箱
	int parameterBox;
};

#endif