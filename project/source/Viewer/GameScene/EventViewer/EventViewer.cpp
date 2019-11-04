//=============================================================================
//
// イベントビュアー管理処理 [EventViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/TMath.h"
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

	PlayMessage();

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
	//メッセージカウンターを0からmessageMexまででラップアラウンド
	Math::WrapAround(0, messageMax, messageSetCnt);

	if (messageSetCnt != 0)
	{
		//ひとつ前のメッセージが再生終了してたならカウントリセット
		if (!eventMessage[messageSetCnt - 1]->isPlaying)
		{
			messageSetCnt = 0;
		}
	}

	//セットカウントをカウントアップ
	messageSetCnt++;
}

//=============================================================================
// メッセージ再生
//=============================================================================
void EventViewer::PlayMessage(void)
{
	//メッセージがなかったらリターン
	if (messageContainer.empty()) return;

	//最後のメッセージがプレイ中なら終わるまでリターン
	if (eventMessage[messageMax - 1]->isPlaying) return;

	//メッセージをカウント
	CountMessage();

	//イベントメッセージをセット
	eventMessage[messageSetCnt - 1]->SetEventMessage(messageContainer[0], messageSetCnt);

	//メッセージコンテナの先頭を削除
	messageContainer.erase(messageContainer.begin());
}

//=============================================================================
// イベント発生メッセージを設置
//=============================================================================
void EventViewer::SetEventMessage(const std::string message)
{
	// イベントメッセージがない
	if (message.empty()) return;

	//メッセージをコンテナの末尾に追加
	messageContainer.push_back(message);
}

//=============================================================================
// イベント発生テロップを設置
//=============================================================================
void EventViewer::SetEventTelop(TelopID id, std::function<void(void)> Callback)
{
	eventTelop->Set(id, Callback);
}