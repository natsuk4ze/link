//=====================================
//
//SpaceGrid.h
//機能:宇宙レベルのグリッド
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SPACEGRID_H_
#define _SPACEGRID_H_

#include "../../../main.h"

/**************************************
前方宣言
***************************************/
class BoardPolygon;

/**************************************
クラス定義
***************************************/
class SpaceGrid : GameObject
{
public:
	SpaceGrid();
	virtual ~SpaceGrid();

	void Update();
	void Draw();

private:
	BoardPolygon * polygon;

	int cntFrame;
};
#endif