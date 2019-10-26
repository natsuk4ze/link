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

#ifdef _DEBUG

#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Input/input.h"

#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventViewer::EventViewer()
{
	eventViewer.push_back(eventTelop = new EventTelop());

	for (int i = 0; i < messageMax; i++)
	{
		eventViewer.push_back(eventMessage[i] = new EventMessage());
	}

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

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_M))
	{
		SetEventMessage("イベント発生！");
	}

	Debug::Begin("EventViewer");
	Debug::Text("MessageSetCnt:%d", messageSetCnt);
	Debug::End();

#endif
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
// メッセージをカウント
//=============================================================================
void EventViewer::CountMessage(void)
{
	//セットカウントをカウントアップ
	messageSetCnt++;

	if (messageSetCnt != 1)
	{
		//ひとつ前のメッセージが再生終了してたならカウントリセット
		if (!eventMessage[messageSetCnt - 2]->isPlaying)
		{
			messageSetCnt = 1;
		}
	}

	if (messageSetCnt > messageMax)
	{
		messageSetCnt = 1;
	}
}

//=============================================================================
// イベント発生メッセージを設置(*仮実装)
//=============================================================================
void EventViewer::SetEventMessage(const std::string Message)
{
	// イベントメッセージがない
	if (Message.empty())
	{
		return;
	}

	CountMessage();
	eventMessage[messageSetCnt - 1]->SetEventMessage(Message, messageSetCnt);
}

//=============================================================================
// イベント発生テロップを設置
//=============================================================================
void EventViewer::SetEventTelop(TelopID id, std::function<void(void)> Callback)
{
	eventTelop->Set(id, Callback);
}
