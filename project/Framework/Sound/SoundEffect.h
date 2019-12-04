//=====================================
//
//SoundEffect.h
//機能:サウンドエフェクト管理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SOUNDEFFECT_H_
#define _SOUNDEFFECT_H_

#include "../../main.h"
#include <dsound.h>
#include <unordered_map>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SE
{
public:
	// SEの種類を列挙
	enum Type
	{
		AIBonus,				// AIレベルにボーナス（茶柱イベント）
		AIOutofControll,		// AI暴走
		AIOutofControllStop,	// AI暴走阻止
		AllLinkLevelUp,			// 全ての町のリンクレベル上昇
		DevelopSpeedUp,			// 発展度上昇
		StockRecovery,			// ドリルのストック回復
		LinkLevelDown,			// 1つの町のリンクレベルダウン
		LinkLevelUp,			// 1つの町のリンクレベルアップ
		MeteorBreakFailed,		// 隕石イベント失敗
		MeteorBreakSuccess,		// 隕石イベント成功
		NewContinent,			// 新大陸出現
		NewStar,				// 新しい星出現
		NewTown,				// 新しい町誕生
		TimeLimitHeal,			// 制限時間回復
		UFOFailed,				// UFOイベント失敗
		UFOSuccess,				// UFOイベント成功
		
		Max
	};
	static const char* path[Type::Max];


	//サウンド読み込み処理
	static void Load(const char* path, int tag);

	//読み込んだサウンドをクリアする処理
	static void Clear();

	//再生処理
	//ボリュームは1.0f ~ 0.0f
	static void Play(int tag, float volume);

	//停止処理
	static void Stop(int tag);
	static void Stop();

	//再開処理
	static void Resume(int tag);
	static void Resume();

private:
	//読み込んだサウンドのコンテナ
	static std::unordered_map<int, LPDIRECTSOUNDBUFFER8> soundContainer;
};
#endif