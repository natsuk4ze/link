//=============================================================================
//
// UDPクライアントクラス [UDPClient.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _UDPClient_H_
#define _UDPClient_H_

#include <string>
#include "PacketConfig.h"
#include "../../source/Event/EventConfig.h"
#include "../../source/Viewer/Framework/ViewerDrawer/TextureDrawer.h"

using std::string;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPClient
{
private:
	SOCKET ClientSocket;
	sockaddr_in ServerAddress;
	TextureDrawer* Text;
	int TimeoutCount = 0;
	DWORD ThreadCount;
	bool ReceiveSuccess = false;
	bool ThreadStop = false;
	unsigned long long LastScore = 0;

	void GetScorePacket(void);

public:
	UDPClient();
	~UDPClient();
	void Update(void);
	void Draw(void);
	void SendRankPacket(string NameStr, string AILevel);
	void SendRankPacket(int NameInt, unsigned long long AILevel);
	void SendEventPacket(string EventNo, string FieldLevel);
	void SendEventPacket(EventConfig::EventType EventNo, int FieldLevel);
	void SendLevelUpPacket(void);
	void RetryGetLastScore(void);
	unsigned long long GetLastScore(void);

	// マルチスレッド用	
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);
	bool InLoading = false;
};

#endif
