//=====================================
//
//SuspendViewer.h
//機能:サスペンドビューワー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SUSPENDVIEWER_H_
#define _SUSPENDVIEWER_H_

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SuspendViewer : public Polygon2D
{
public:
	enum Dialog
	{
		Yes,
		No,
		DialogMax
	};

	SuspendViewer();
	~SuspendViewer();

	void Update();
	void Draw();
	
	Dialog GetSelected() const;

private:
	Polygon2D *dialogYes, *dialogNo;
	Polygon2D *bg;

	bool selectedYes;
};
#endif