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
		InsertRank,		// ランキング追加
		EventLive,		// イベント中継
		LevelUp,		// レベルアップ
		GetLastScore,	// 最下位のスコアを取得
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

// パケットの先頭文字列
const string PacketHeader = "これはLink専用の通信パケットです";	

#endif