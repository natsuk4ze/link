//=====================================
//
// ガイドビュアーバックグラウンド[GuideViewerBG.h]
// 機能：ガイドビュアーの背景
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDEVIEWERBG_H_
#define _GUIDEVIEWERBG_H_

#include "../../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../../Framework/Core/GameObject.h"

//**************************************
// クラス定義
//**************************************
class GuideViewerBG :
	public GameObject
{
private:
	BoardPolygon* polygon;
public:
	GuideViewerBG();
	~GuideViewerBG();

	void Update();
	void Draw();
};

#endif
