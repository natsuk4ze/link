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
// コンストラクタ
//*****************************************************************************
EventViewer::EventViewer()
{
	eventViewer.push_back(eventTelop = new EventTelop());
	eventViewer.push_back(eventMessage = new EventMessage());

	eventViewerMax = eventViewer.size();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventViewer::~EventViewer()
{
	//インスタンスを入れた配列をクリア
	eventViewer.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void EventViewer::Update()
{
	for (int i = 0; i < eventViewerMax; i++)
	{
		eventViewer[i]->Update();
	}
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

	for (int i = 0; i < eventViewerMax; i++)
	{
		eventViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// イベント発生メッセージを設置
//=============================================================================
void EventViewer::SetEventMessage(const std::string Message)
{
	eventMessage->Set(Message);
}