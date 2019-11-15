//=====================================
//
// ガイドビュアーエフェクト[GuideViewerEffect.h]
// 機能：ガイドビュアーのエフェクト
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDEVIEWEREFFECT_H_
#define _GUIDEVIEWEREFFECT_H_

#include "../../../../Framework/Core/GameObject.h"
#include "../../../../Framework/Renderer2D/Polygon2D.h"

//**************************************
// クラス定義
//**************************************
class GuideViewerEffect :
	public GameObject
{
private:
	Polygon2D* polygon;

public:
	GuideViewerEffect();
	~GuideViewerEffect();

	void Update();
	void Draw();
};

#endif

