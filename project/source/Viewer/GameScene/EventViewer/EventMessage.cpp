//=============================================================================
//
// イベントメッセージ処理 [EventMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "EventMessage.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventMessage::EventMessage()
{
	//テキスト
	text = new TextViewer("cinecaption", 50);

	////背景
	//bg = new BaseViewerDrawer();
	////bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/EventMessage/BG.png");
	//bg->MakeVertex();
	//bg->size = D3DXVECTOR3(204.80f, 51.20f, 0.0f);
	//bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.3, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	//bg->SetColor(SET_COLOR_NOT_COLORED);

	//isPlaying = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventMessage::~EventMessage()
{
	SAFE_DELETE(text);
	//SAFE_DELETE(bg);
}

//=============================================================================
// 更新処理
//=============================================================================
void EventMessage::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void EventMessage::Draw(void)
{
	////背景を先に描画
	//bg->Draw();
	//bg->SetVertex();

	text->Draw();
}

//=============================================================================
// メッセージセット処理
//=============================================================================
void EventMessage::SetEventMessage(const std::string Message)
{
	text->SetText(Message);
	text->SetPos(1600, 900);
}
