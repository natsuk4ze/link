//=============================================================================
//
// ストックビュアー処理 [ItemStockViewer.h]
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
class ItemStockViewer :public BaseViewer
{
public:
	ItemStockViewer();
	~ItemStockViewer();

	void Update(void);
	void Draw(void);

	//パラメータを受けとる箱
	int parameterBox;

private:
	BaseViewerDrawer *icon;
	CountViewerDrawer *num;

	//アニメーション
	void Hop(void);

	//現在のパラメータ
	int currentParam;

	//１フレーム前のパラメータ
	int lastParam;
};


#endif