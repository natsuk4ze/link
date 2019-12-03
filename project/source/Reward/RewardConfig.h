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
		ButtonMashing,	// ボタン連打イベント○回クリア
		Destructer,		// 山破壊○回
		Artist,			// 橋を架ける○個
		Linker,			// 町のリンクレベル○レベル到達
		MinusMaster,	// マイナスイベント○回
		PlusMaster,		// プラスイベント○回
		Pioneer,		// 道を○個
		MasterAI,		// AIレベル○レベルに到達
		MinusComplete,	// マイナスイベントコンプリート
		PlusComplete,	// プラスイベントコンプリート
		Max
	};

	// リワード到達確認のためのデータ
	static const int MaxData[] = {3, 20, 15, 15, 10, 20, 250, 10000, 4, 7};
}

#endif
