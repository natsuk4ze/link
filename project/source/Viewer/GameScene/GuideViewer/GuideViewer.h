//=====================================
//
// ガイドビュアー[GuideViewer.h]
// 機能：ガイド役キャラクター表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDEVIEWER_H_
#define _GUIDEVIEWER_H_

#include "../../../../Framework/PostEffect/Effect/CRTFilter.h"
#include <string>
#include "GuideActor.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class GuideCamera;
class GuideViewerBG;
class GuideCallOutViewer;
class SubScreen;

//**************************************
// クラス定義
//**************************************
class GuideViewer
{
private:
	// 各種インスタンス用ポインタ
	GuideActor* actor;
	GuideCamera* camera;
	GuideViewerBG* bg;
	CRTFilter* filter;
	GuideCallOutViewer *callOutViewer;
	SubScreen* subScreen;

	bool isActive;	// 描画可否判定

	static const D3DXVECTOR2 SubScreenPosition;
	static const D3DXVECTOR2 SubScreenSize;

public:
	GuideViewer();
	~GuideViewer();

	void Update();
	void Draw();

	void ChangeAnim(GuideActor::AnimState next);
	void SetActive(bool flag);

	//ガイドビュアーセット
	void SetGuideViewer(const std::string &message);
};

#endif
