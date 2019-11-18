//=============================================================================
//
// UDPサーバークラス [UDPServer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _UDPServer_H_
#define _UDPServer_H_

#include <vector>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPServer
{
private:
	SOCKET ServerSocket;

	void ReceivePacket(void);

#if _DEBUG
	std::vector<sockaddr_in> ConnectedList;
#endif

public:
	UDPServer();
	~UDPServer();

	// マルチスレッド用
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);
};

#endif
