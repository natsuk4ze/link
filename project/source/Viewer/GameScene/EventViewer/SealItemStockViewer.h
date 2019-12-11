//=============================================================================
//
// ストック封印ビュアー処理 [SealItemStockViewer.h]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#ifndef _SEAL_STOCK_VIEWER_H_
#define _SEAL_STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SealItemStockViewer :public BaseViewer
{
private:
	//アイコン
	TextureDrawer *Icon;
	TextureDrawer *Icon_White;

	void CountDownStart(void);

public:
	SealItemStockViewer();
	~SealItemStockViewer();

	void Update(void);
	void Draw(void);
	void SetBanIcon(void);
};


#endif