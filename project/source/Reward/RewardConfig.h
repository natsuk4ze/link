//=====================================
//
// リワードコンフィグ[RewardConfig.cpp]
// 機能：各リワード関連の情報まとめ
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _REWARDCONFIG_H_
#define _REWARDCONFIG_H_

namespace RewardConfig
{
	// リワードの種類
	enum Type
	{
		ButtonMashing,	// ボタン連打イベント○回クリアOK
		Destructer,		// 山破壊○回OK
		Artist,			// 橋を架ける○個OK
		Linker,			// 町のリンクレベル○レベル到達OK
		MinusMaster,	// マイナスイベント○回OK
		PlusMaster,		// プラスイベント○回OK
		Pioneer,		// 道を○個OK
		MasterAI,		// AIレベル○レベルに到達OK
		MinusComplete,	// マイナスイベントコンプリートOK
		PlusComplete,	// プラスイベントコンプリートOK
		Max
	};

	// リワード到達確認のためのデータ
	static const int MaxData[] = {3, 20, 15, 5, 10, 20, 250, 10, 4, 7};
}

#endif
