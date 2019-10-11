//=============================================================================
//
// イベントテロップ処理 [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "EventTelop.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventTelop::EventTelop()
{
	//テキスト
	text = new BaseViewerDrawer();
	//text->LoadTexture("data/TEXTURE/Viewer/GameViewer/EventTelop/Number.png");
	text->MakeVertex();
	text->size = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.5f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	text->SetColor(SET_COLOR_NOT_COLORED);

	//背景
	bg = new BaseViewerDrawer();
	//bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/EventTelop/BG.png");
	bg->MakeVertex();
	bg->size = D3DXVECTOR3(204.80f, 51.20f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.3, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventTelop::~EventTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// 更新処理
//=============================================================================
void EventTelop::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void EventTelop::Draw(void)
{
	//背景を先に描画
	bg->Draw();
	bg->SetVertex();

	text->Draw();
	text->SetVertex();
}

////=============================================================================
//// テロップセット処理
////=============================================================================
//void EventTelop::Set(TelopID id, DelegateBase onFinish)
//{
//
//}
