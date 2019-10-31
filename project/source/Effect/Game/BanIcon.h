//=============================================================================
//
// ストックビュアー処理 [BanIcon.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STOCK_VIEWER_H_
#define _STOCK_VIEWER_H_

#include "../../Viewer/Framework/BaseViewer.h"
#include "../../Viewer/Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BanIcon :public BaseViewer
{
public:
	BanIcon();
	~BanIcon();

	void Update(void);
	void Draw(void);
	void Init(void);

private:
	int RemainFrame;
	bool IsPlaying;
	BaseViewerDrawer *Icon;			
	BaseViewerDrawer *Icon1;		
	BaseViewerDrawer *Icon2;		
	BaseViewerDrawer *Icon2_White;	

	//アニメーション
	void Animate(void);
	void SetVertex(float Percent);
	void SetTexture(float Percent);
};


#endif