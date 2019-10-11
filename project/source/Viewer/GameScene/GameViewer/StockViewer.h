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
class GameViewer;

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

	BaseViewerDrawer * icon[stockViewerMax];
	BaseViewerDrawer *iconBG[stockViewerMax];
	BaseViewerDrawer *numBG[stockViewerMax];
	CountViewerDrawer *num[stockViewerMax];
	GameViewer *gameViewer;

	void UpdateParam(void);
	void Animate(void);

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

	const float hopNumValue = 30.0f;
	const D3DXVECTOR3 initNumSize = D3DXVECTOR3(7.50f, 15.0f, 0.0f);
};


#endif