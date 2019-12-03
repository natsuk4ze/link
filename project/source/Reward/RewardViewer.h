//=====================================
//
// リワードビュアー[RewardViewer.h]
// 機能：各リワードを表示するクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _REWARDVIEWER_H_
#define _REWARDVIEWER_H_

#include "RewardController.h"

class AchieveViewer;
namespace RC = RewardConfig;
//**************************************
// クラス定義
//**************************************
class RewardViewer
{
private:
	AchieveViewer* achieveViewer;
	bool achieved[RC::Type::Max];

public:
	RewardViewer();
	~RewardViewer();

	void Update();
	void Draw();

	void CheckAchieved();
	void ResetAchieved();
};

#endif
