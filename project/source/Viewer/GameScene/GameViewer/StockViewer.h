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

	//ストックビュアーの種類
	enum StockViewerType
	{
		Bridge,
		Drill,
		Insurance,
		EDF
	};

	//ストックビュアーの種類数
	static const int typeMax = 4;

	//パラメータを受けとる箱
	int parameterBox[typeMax];

private:
	BaseViewerDrawer *icon[typeMax];
	CountViewerDrawer *num[typeMax];

	//アニメーション
	void Animate(void);
};


#endif