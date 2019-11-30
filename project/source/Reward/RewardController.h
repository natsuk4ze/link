//=====================================
//
// リワードコントローラ[RewardController.h]
// 機能：各リワードをコントロールするクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _REWARDCONTROLLER_H_
#define _REWARDCONTROLLER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"
#include <map>
#include <string>

class Reward;
//**************************************
// クラス定義
//**************************************
class RewardController :
	public BaseSingleton<RewardController>
{
	friend class BaseSingleton<RewardController>;
public:
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

	// リワードの作成、削除
	void Create(Type type, int maxData);
	void AllDelete();

	// 各リワードの到達確認
	bool CheckAchieved(Type rewardType);
	bool CheckFirstAchieved(Type rewardType);

	// リワード到達者の名前を確認（一文字ずつ）
	int GetName(Type rewardType, int alphabetNo);

	// 各リワードのデータをセット
	void SetRewardData(Type rewardType, int data);

	// 各リワードのデータをリセット
	void ResetRewardData();

	// リワード到達確認のためのデータ
	static const int MaxData[Max];

private:
	RewardController() {}
	~RewardController() {}

	std::map<Type, Reward*> rewardPool;
};

#endif