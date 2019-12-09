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

	// リワード到達確認のためのデータ
	static const char* RewardName[] =
	{
		"連打の鬼",
		"抑えられない破壊衝動",
		"アーチスト",
		"ここが全ての中心",
		"上を向いて歩こう！",
		"このイベント良い弁当",
		"我が道を行く",
		"最高峰のAI",
		"これ以上無い不幸...",
		"もう絶望する必要なんて無い",
	};
	
}

#endif
