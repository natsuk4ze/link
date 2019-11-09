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
	CountViewerDrawer();
	~CountViewerDrawer();

	void DrawCounter(int baseNumber, int parameterBox, int placeMax,
		float intervalNumberScr, float intervalNumberTex);

	void DrawCounter(int baseNumber, int parameterBox,
		float intervalNumberScr, float intervalNumberTex);

	//スクリーン上の表示座標間隔
	float intervalPosScr;

	//テクスチャ素材の表示座標間隔
	float intervalPosTex;

	//桁数
	int placeMax;

	//進数　
	int baseNumber;

	//ホップアニメーション関連変数
	float HopNumber(float sizeY, float initSizeY, float hopValue);
	bool isHopped;
	float radian;
	const float hopSpeed = D3DX_PI / 10;

private:
	void Draw();

	void SetVertexPos(int placeCount, float placeInterval);
	void SetTexture(int number, float placeInterval);

	int texDivX = 4;
	int texDivY = 3;
};

#endif

