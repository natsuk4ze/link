//=====================================
//
// アチーブビュアー[AchieveViewer.h]
// 機能：リワードを達成したときに通達を行うビュアー
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _ACHIEVEVIEWER_H_
#define _ACHIEVEVIEWER_H_

#include "../../Framework/Renderer2D/Polygon2D.h"

//**************************************
// クラス定義
//**************************************
class AchieveViewer
{
private:
	Polygon2D* polygon;
	int index;					// 使用するテクスチャ番号
	bool active;
	int cntFrame;
	D3DXVECTOR3 movePosition;

	static const int DivideX;
	static const int DivideY;
	static const float SizeX;
	static const float SizeY;
	static const float MoveValue;
	static const D3DXVECTOR3 InitPosition;

public:
	AchieveViewer();
	~AchieveViewer();

	void Update();
	void Draw();

	void SetIndex(int index);
	void SetActive();
};

#endif
