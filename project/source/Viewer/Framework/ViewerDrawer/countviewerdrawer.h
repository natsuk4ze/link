//=============================================================================
//
// カウントビュアー描画処理 [CountViewerDrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COUNT_VIEWER_DRAWER_H_
#define _COUNT_VIEWER_DRAWER_H_

#include "CountViewerDrawer.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CountViewerDrawer :public BaseViewerDrawer
{
public:
	void DrawCounter(int baseNumber, int parameterBox, int placeMax,
		float intervalNumberScr, float intervalNumberTex);

	//パラメータを受けとる箱
	int parameterBox;

	//スクリーン上の表示間隔
	float intervalNumberScr;

	//テクスチャ素材のの表示間隔
	float intervalNumberTex;

	//桁数
	int placeMax;

	//進数　
	int baseNumber;

private:
	void SetVertex(int placeCount, float placeInterval);
	void SetTexture(int number, float placeInterval);

};

#endif

