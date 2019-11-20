//=============================================================================
//
// UDPクライアントクラス [UDPClient.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _UDPClient_H_
#define _UDPClient_H_

#include "PacketConfig.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPClient
{
private:
	SOCKET ClientSocket;
	sockaddr_in ServerAddress;
	PacketConfig Packet;

public:
	UDPClient();
	~UDPClient();
	void SendPacket();
	void ReceivePacketConfig(PacketConfig Packet);
};

#endif
