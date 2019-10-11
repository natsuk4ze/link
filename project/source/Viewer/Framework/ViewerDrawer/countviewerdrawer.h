//=============================================================================
//
// カウントビュアー描画処理 [CountViewerDrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COUNT_VIEWER_DRAWER_H_
#define _COUNT_VIEWER_DRAWER_H_

#include "BaseViewerDrawer.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CountViewerDrawer :public BaseViewerDrawer
{
public:
	void DrawCounter(int baseNumber, int parameterBox, int placeMax,
		float intervalNumberScr, float intervalNumberTex);

	//スクリーン上の表示間隔
	float intervalNumberScr;

	//テクスチャ素材のの表示間隔
	float intervalNumberTex;

	//桁数
	int placeMax;

	//進数　
	int baseNumber;

	//ホップアニメーション関連変数
	float HopNumber(float sizeY, float initSizeY, float hopValue);
	bool isHopped;
	float radian;
	const float hopSpeed = D3DX_PI/10;

private:
	void SetVertex(int placeCount, float placeInterval);
	void SetTexture(int number, float placeInterval);

};

#endif

