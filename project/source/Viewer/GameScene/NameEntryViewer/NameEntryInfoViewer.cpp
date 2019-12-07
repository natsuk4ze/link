//=============================================================================
//
// 名前入力背景処理 [NameEntryInfoViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryInfoViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
NameEntryInfoViewer::NameEntryInfoViewer()
{
	bg = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 1.30f), D3DXVECTOR2(600.0f, 512.0f/4),
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryInfoViewer/BG.png");

	text = new TextViewer("data/FONT/Makinas-4-Square.otf", 50);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 7.50f), (int)(SCREEN_HEIGHT / 1.30f));
	text->SetText("名前を入力してね");
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
NameEntryInfoViewer::~NameEntryInfoViewer()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(text);
}

//=============================================================================
// 更新処理
//=============================================================================
void NameEntryInfoViewer::Update(void)
{
	FadeText();
}

//=============================================================================
// 描画処理
//=============================================================================
void NameEntryInfoViewer::Draw(void)
{
	bg->Draw();
	text->Draw();
}

//=============================================================================
// フェード処理
//=============================================================================
void NameEntryInfoViewer::FadeText()
{
	alpha+= 0.03f;
	text->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	alpha = Math::WrapAround(0.0f, 1.0f, alpha);
}
