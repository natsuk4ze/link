//=============================================================================
//
// イベントコンフィグ [EventConfig.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _EventConfig_H_
#define _EventConfig_H_

namespace EventConfig
{
	enum EventType
	{
		CityLevelUp,		// 町の発展レベル上昇
		NewCity,			// 新しい町、国、星出現
		StockRecovery,		// 橋、ドリルのストック数を増やす
		FamousPeople,		// 町に「有名人がいる状態」付与。数秒間発展スピード上昇
		Bonus,				// 全体にボーナス、特定の町に更にボーナス
		AILevelUp,			// スロットを回してAI発展レベルにボーナス
		CityLevelDecrease,	// 町の発展レベル減少
		CityDestroy,		// 町消滅
		AILevelDecrease,	// AI発展レベル減少
		MoveInverse,		// 操作反転（上下左右）
		BanStockUse,		// 一定時間特殊チップ使用不可
		CongestionUp,		// 交差点の混雑度一定時間上昇
		NoEvent = -1,		// イベントなし
	};
}

#endif