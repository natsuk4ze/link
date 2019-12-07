//=============================================================================
//
// 名前入力リール処理処理 [NameEntryBgViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryBgViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
NameEntryBgViewer::NameEntryBgViewer()
{
	//リールの座標間隔
	const float intervalReelPos = 130.0f;

	congratsText = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.0f, SCREEN_HEIGHT/2.50f),D3DXVECTOR2(900.0f, 900/8.0f), 
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryBgViewer/CongratsText.png");

	congratsText->SetTexture(1,8, 0);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
NameEntryBgViewer::~NameEntryBgViewer()
{
	for (int i = 0; i < entryNameMax; i++)
	{
		SAFE_DELETE(congratsText);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void NameEntryBgViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void NameEntryBgViewer::Draw(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		//背景を先に描画
		congratsText->Draw();
	}
}