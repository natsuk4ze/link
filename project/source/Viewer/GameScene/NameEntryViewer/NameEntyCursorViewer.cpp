//=============================================================================
//
// 名前入力カーソル処理処理 [NameEntryCursorViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Input/input.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "NameEntryCursorViewer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//リールの座標間隔
static const float intervalReelPos = 130.0f;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
NameEntryCursorViewer::NameEntryCursorViewer()
{
	//カーソル
	cursor = new BaseViewerDrawer();
	cursor->LoadTexture("data/TEXTURE/Viewer/NameEntryViewer/NameEntryCursorViewer/Cursor.png");
	cursor->size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	cursor->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 7.0f, SCREEN_HEIGHT / 10 * 8.0f, 0.0f);
	cursor->MakeVertex();
	cursor->SetTexture(2, 2, 0);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
NameEntryCursorViewer::~NameEntryCursorViewer()
{
	SAFE_DELETE(cursor);
}

//=============================================================================
// 更新処理
//=============================================================================
void NameEntryCursorViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void NameEntryCursorViewer::Draw(void)
{
	cursor->Draw();
}

//=============================================================================
// カーソル座標を右に移動処理
//=============================================================================
void NameEntryCursorViewer::MoveCursorRight()
{
	cursor->position.x += intervalReelPos;
}

//=============================================================================
// カーソル座標を左に移動処理
//=============================================================================
void NameEntryCursorViewer::MoveCursorLeft()
{
	cursor->position.x -= intervalReelPos;
}