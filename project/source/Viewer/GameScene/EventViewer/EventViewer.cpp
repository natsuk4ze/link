//=============================================================================
//
// イベントビュアー管理処理 [EventViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include <vector>
#include "EventMessage.h"
#include "EventTelop.h"
#include "EventViewer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventViewer::EventViewer()
{
	eventTelop = new EventTelop();
	eventMessage = new EventMessage();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventViewer::~EventViewer()
{
	SAFE_DELETE(eventTelop);
	SAFE_DELETE(eventMessage);
}

//=============================================================================
// 更新処理
//=============================================================================
void EventViewer::Update()
{
	eventTelop->Update();
	eventMessage->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void EventViewer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	eventTelop->Draw();
	eventMessage->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
