//=============================================================================
//
// 回転ビュアー描画用処理 [RotateViewerDrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _ROTATE_VIEWER_DRAWER_H_
#define _ROTATE_VIEWER_DRAWER_H_

#include "BaseViewerDrawer.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RotateViewerDrawer :public BaseViewerDrawer
{
public:
	RotateViewerDrawer();
	~RotateViewerDrawer();

	void MakeVertex();
	void SetVertexPos();
	void CreateCircle();

private:
	float baseAngle;
	float radius;
};

#endif

