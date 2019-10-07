//=============================================================================
//
// ストックビュアー処理 [StockViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STOCK_VIEWER_H_
#define _STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class StockViewer :public BaseViewer
{
public:
	StockViewer();
	~StockViewer();

	void Update(void);
	void Draw(void);

private:
	static const int stockViewerMax = 4;
	const float intervalViewerPos = 185.0f;

	enum StockViewerType
	{
		Bridge,
		Drill,
		Insurance,
		EDF
	};

	//アイテムアイコンテクスチャパス
	const char *iconTexPath[stockViewerMax]
	{
		"data/TEXTURE/Viewer/GameViewer/StockViewer/Bridge/BridgeIcon.png",
		"data/TEXTURE/Viewer/GameViewer/StockViewer/Drill/DrillIcon.png",
		"data/TEXTURE/Viewer/GameViewer/StockViewer/Insurance/InsuranceIcon.png",
		"data/TEXTURE/Viewer/GameViewer/StockViewer/EDF/EDF_Icon.png",
	};

	////ホッピング関連変数
	//void HopNumber(int StockViewerType);
	////bool isHopped;
	//float radian;
	//const float hopValue = 30.0f;
	//const float hopSpeed = 0.20f;
	//const D3DXVECTOR3 initSizeNumber = D3DXVECTOR3(7.50f, 15.0f, 0.0f);


	BaseViewerDrawer *icon[stockViewerMax];
	BaseViewerDrawer *iconBG[stockViewerMax];
	BaseViewerDrawer *numBG[stockViewerMax];
	CountViewerDrawer *num[stockViewerMax];

};


#endif