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
class ViewerAnimater;

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
	enum TextType
	{
		Ready,
		Go,
		Max
	};

	BaseViewerDrawer *readyText;
	BaseViewerDrawer *goText;
	ViewerAnimater *anim[TextType::Max];

	//レディーすべきか
	bool shouldReady;
	//ゴーすべきか
	bool shouldGo;
};

#endif