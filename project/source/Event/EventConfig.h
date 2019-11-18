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
		LinkLevelUp,		// 一つの町のリンクレベル上昇
		NewCity,			// 新しい町、国、星出現
		StockRecovery,		// ドリルのストック数を増やす
		FamousPeople,		// 街の発展度計算に倍率をかける
		AllLinkLevelUp,		// 道が繋がっている街全体のリンクレベル上昇
		AILevelUp,			// スロットを回してAI発展レベルにボーナス
		TimeRecovery,		// 制限時間の回復
		CityDestroy,		// 町消滅
		AILevelDecrease,	// AI発展レベル減少
		BanStockUse,		// 一定時間特殊チップ使用不可
		LinkLevelDecrease,	// 町のリンクレベル減少
		NoEvent = -1,		// イベントなし
	};
}

#endif