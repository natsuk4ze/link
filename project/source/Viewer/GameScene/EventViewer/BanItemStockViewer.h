//=============================================================================
//
// バンストックビュアー処理 [BanItemStockViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BAN_STOCK_VIEWER_H_
#define _BAN_STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BanItemStockViewer :public BaseViewer
{
public:
	BanItemStockViewer();
	~BanItemStockViewer();

	void Update(void);
	void Draw(void);

	//パラメータを受けとる箱
	bool parameterBox;

private:

	//アイコン
	BaseViewerDrawer *icon;		

	//アニメーション
	void Play(void);

	//現在のパラメータ
	bool currentParam;

	//１フレーム前のパラメータ
	bool lastParam;
};


#endif