//=============================================================================
//
// 送信パケットパラメータクラス [PacketConfig.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _PacketConfig_H_
#define _PacketConfig_H_

#include <string>

using namespace std;

namespace Packet
{
	enum
	{
		InsertRank,
		EventLive,
		LevelUp,
		GetLastScore,
	};

	enum
	{
		Header = 0,
		Type = 1,
		// ランキング追加用
		PlayerName = 2,
		AILevel = 3,
		// イベント発生用
		EventNo = 2,
		FieldLevel = 3,
		Max,
	};
}

// 使用するポート番号
const int ServerPort = 8080;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class PacketConfig
{
public:
	string Header = "これはLink専用の通信パケットです";	// パケットの先頭文字列
	int PacketType = 0;									// 起こる事件を種類
	string PlayerName = "Potato";						// プレイヤーの名前
	int AILevel = 0;									// AIレベル
};

#endif