//=====================================
//
// ガイドビュアーバックグラウンド[GuideViewerBG.h]
// 機能：ガイドビュアーの背景
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDEVIEWERBG_H_
#define _GUIDEVIEWERBG_H_

#include <vector>
using std::vector;

class PolygonDrawer;

//**************************************
// クラス定義
//**************************************
class GuideViewerBG
{
private:
	int CountFrame;

	PolygonDrawer* background;
	vector<PolygonDrawer*> LeftWall;
	vector<PolygonDrawer*> RightWall;

public:
	GuideViewerBG();
	~GuideViewerBG();
	void Update(void);
	void Draw(void);
};

#endif
