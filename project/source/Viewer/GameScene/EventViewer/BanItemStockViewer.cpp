//=============================================================================
//
// バンストックビュアー処理 [BanItemStockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "../../../../Framework/Math/Easing.h"
#include "BanItemStockViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
BanItemStockViewer::BanItemStockViewer()
{
	//バツアイコン
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/EventViewer/BanStockViewer/BanStock.png");
	icon->size = D3DXVECTOR3(400.0f, 400.0f, 0.0f);
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.5f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BanItemStockViewer::~BanItemStockViewer()
{
	SAFE_DELETE(icon);
}

//=============================================================================
// 更新処理
//=============================================================================
void BanItemStockViewer::Update(void)
{
	//アニメーション
	Play();
}

//=============================================================================
// 描画処理
//=============================================================================
void BanItemStockViewer::Draw(void)
{
	//ストックバン中なら描画描画
	if (parameterBox == true) return;

	icon->Draw();
}

//=============================================================================
// アニメーション処理
//=============================================================================
void BanItemStockViewer::Play(void)
{

}
