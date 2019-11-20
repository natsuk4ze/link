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

//=============================================================================
// コンストラクタ
//=============================================================================
UDPClient::UDPClient()
{
	// WinSock初期化
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ソケット生成
	ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// ブロードキャスト許可
	int value = 1;
	setsockopt(ClientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&value, sizeof(value));

	// 送信先アドレス
	ServerAddress.sin_port = htons(ServerPort);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = inet_addr("255.255.255.255");//ブロードキャストアドレス
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPClient::~UDPClient()
{
	// WinSock終了処理
	closesocket(ClientSocket);
	WSACleanup();
}

//=============================================================================
// パケット送信
//=============================================================================
void UDPClient::SendPacket()
{
	// データ送信
	string Message;
	int AddressLength;

	AddressLength = sizeof(ServerAddress);

	// 入力メッセージ処理
	Message = Packet.Header + "," + Packet.PlayerName + "," + std::to_string(Packet.AILevel);

	// 送信
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// パケット送信
//=============================================================================
void UDPClient::ReceivePacketConfig(const PacketConfig Packet)
{
	this->Packet = Packet;
}