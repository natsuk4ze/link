//=============================================================================
//
// UDPクライアントクラス [UDPClient.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "UDPClient.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
HANDLE UDPClient::Thread = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
UDPClient::UDPClient()
{
	Text = new TextureDrawer(D3DXVECTOR2(450.0f, 150.0f), 1, 2);
	Text->LoadTexture("data/TEXTURE/Viewer/ResultViewer/NetworkText.png");
	//Text->LoadTexture("data/TEXTURE/Viewer/ResultViewer/Text.png");
	Text->SetPosition(D3DXVECTOR3(1600.0f, 100.0f, 0.0f));

	// WinSock初期化
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ソケット生成
	ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// 送信先アドレス
	ServerAddress.sin_port = htons(ServerPort);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = inet_addr("255.255.255.255");//ブロードキャストアドレス

	// ブロードキャスト許可
	int value = 1;
	setsockopt(ClientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&value, sizeof(value));

	// クライアント受信スレッド開始
	Thread = (HANDLE)_beginthreadex(NULL, 0, ThreadEntryPoint, this, 0, NULL);
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPClient::~UDPClient()
{
	ThreadStop = true;

	// WinSock終了処理
	closesocket(ClientSocket);
	WSACleanup();

	// ===============================================================
	// 注意。きちんとスレッド終了関数(_endthreadex)を呼ばないと
	// メインスレッドが終了した後に他のスレッドはそのまま実行します
	// 例外スローの可能性が高い
	// ===============================================================
	// スレッドが解放するまで待つ
	DWORD ThreadResult = WaitForSingleObject(Thread, INFINITE);
	if (ThreadResult == WAIT_OBJECT_0)
	{
		// スレッド終了
		CloseHandle(Thread);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UDPClient::Update(void)
{
	Text->Update();

	//if (!InMultiThread)
	//	return;

	//DWORD Result = WaitForSingleObject(Thread, 0);
	//// スレッド正常終了
	//if (Result == WAIT_OBJECT_0)
	//{
	//	Thread = 0;
	//	InMultiThread = false;
	//	TimeoutCount = 0;
	//}
	//// タイムアウト
	//else if (Result == WAIT_TIMEOUT)
	//{
	//	TimeoutCount++;
	//	// 10回リクエスト、応答がなかったら更新終了
	//	RetryGetLastScore();
	//	if (TimeoutCount >= 10)
	//	{
	//		InMultiThread = false;
	//		TimeoutCount = 0;
	//	}
	//}
}

void UDPClient::Draw(void)
{
	if (!InLoading)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	Text->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// ランキング追加パケット送信
//=============================================================================
void UDPClient::SendRankPacket(string NameStr, string AILevel)
{
	string Message;

	// 入力メッセージ処理
	Message = PacketHeader + "," + std::to_string(Packet::InsertRank) + "," + NameStr + "," + AILevel;

	// 送信
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// ランキング追加パケット送信
//=============================================================================
void UDPClient::SendRankPacket(int NameInt, unsigned long long AILevel)
{
	string NameStr = std::to_string(NameInt);
	string AILevelStr = std::to_string(AILevel);
	SendRankPacket(NameStr, AILevelStr);
}

//=============================================================================
// イベント中継パケット送信
//=============================================================================
void UDPClient::SendEventPacket(string EventNo, string FieldLevel)
{
	string Message;

	// 入力メッセージ処理
	Message = PacketHeader + "," + std::to_string(Packet::EventLive) + "," + EventNo + "," + FieldLevel;

	// 送信
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// イベント中継パケット送信
//=============================================================================
void UDPClient::SendEventPacket(EventConfig::EventType EventNo, int FieldLevel)
{
	string EventNoStr = std::to_string(EventNo);
	string FieldLevelStr = std::to_string(FieldLevel);
	SendRankPacket(EventNoStr, FieldLevelStr);
}

//=============================================================================
// フィールドレベルアップパケット送信
//=============================================================================
void UDPClient::SendLevelUpPacket(void)
{
	string Message;

	// 入力メッセージ処理
	Message = PacketHeader + "," + std::to_string(Packet::LevelUp);

	// 送信
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// セカンドスレッド
//=============================================================================
unsigned __stdcall UDPClient::ThreadEntryPoint(void* This)
{
	UDPClient* Temp = (UDPClient*)This;
	//Temp->InMultiThread = true;
	Temp->GetScorePacket();					// 本当のセカンドスレッドの処理関数
	_endthreadex(0);					// スレッドの実行停止
	return 0;
}

//=============================================================================
// サーバーからランキング最下位のスコアを取得
//=============================================================================
void UDPClient::GetScorePacket(void)
{
	// データ送信
	char data[256];
	string Message;
	int AddressLength;

	AddressLength = sizeof(ServerAddress);

	while (!ThreadStop)
	{
		memset(data, 0, sizeof(data));

		// メッセージ受信
		recvfrom(ClientSocket, (char*)data, sizeof(data), 0, (sockaddr*)&ServerAddress, &AddressLength);

		// データ処理
		Message = data;
		if (!Message.empty())
		{
			LastScore = std::stoull(Message);
			ReceiveSuccess = true;
			//ThreadCount = SuspendThread(Thread);
		}
		//else
		//{
		//	break;
		//}
	}
}

//=============================================================================
// セカンドスレッド
//=============================================================================
void UDPClient::RetryGetLastScore(void)
{
	// データ送信
	string Message;
	int AddressLength;
	//InMultiThread = true;

	AddressLength = sizeof(ServerAddress);

	// 入力メッセージ処理
	Message = PacketHeader + "," + std::to_string(Packet::GetLastScore);

	// 送信
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, AddressLength);
}

unsigned long long UDPClient::GetLastScore(void)
{
	ReceiveSuccess = false;
	TimeoutCount = 0;
	InLoading = true;
	Text->SetAlpha(1.0f);

	// スレッドまだ解放されないので、もう一度サーバーにリクエスト
	RetryGetLastScore();

	while (TimeoutCount <= 60)
	{
		DWORD Result = WaitForSingleObject(Thread, 1);

		// スレッド正常終了
		if (ReceiveSuccess)
		{
			break;
		}
		// タイムアウト
		else
		{
			TimeoutCount++;

			// リクエスト
			if (TimeoutCount % 3 == 0)
				RetryGetLastScore();
		}
	}

	if (ReceiveSuccess)
	{
		// 成功
		Text->SetIndex(0);
		Text->Fade(60.0f, 0.0f, [&]()
		{
			InLoading = false;
		});
		return LastScore;
	}
	else
	{
		// 失敗
		Text->SetIndex(1);
		Text->Fade(60.0f, 0.0f, [&]()
		{
			InLoading = false;
		});
		return 0;
	}
}
