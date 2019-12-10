//=====================================
//
// RewardNotifierクラス[RewardNotifier.h]
// 機能：ゲーム内リワード達成を通知するクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _RewardNotifier_H_
#define _RewardNotifier_H_

#include "RewardController.h"

class AchieveViewer;
namespace RC = RewardConfig;
//**************************************
// クラス定義
//**************************************
class RewardNotifier
{
private:
	AchieveViewer* achieveViewer;
	bool achieved[RC::Type::Max];

public:
	RewardNotifier();
	~RewardNotifier();

	void Update();
	void Draw();

	void CheckAchieved();
	void ResetAchieved();
};

#endif
