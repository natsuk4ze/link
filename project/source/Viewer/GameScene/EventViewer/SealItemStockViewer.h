//=============================================================================
//
// ストック封印ビュアー処理 [SealItemStockViewer.h]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#ifndef _SEAL_STOCK_VIEWER_H_
#define _SEAL_STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

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
	std::function<bool(void)> GetInPause;

	void CountDownStart(void);

public:
	SealItemStockViewer();
	~SealItemStockViewer();

	void Update(void);
	void Draw(void);
	void SetBanIcon(std::function<bool(void)> func);
	void Reset(void);
};


#endif