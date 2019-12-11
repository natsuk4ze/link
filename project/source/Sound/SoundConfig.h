//=====================================
//
// SoundConfig.h
// 機能:サウンド設定
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SOUNDCONFIG_H_
#define _SOUNDCONFIG_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SoundConfig
{
public:
	// BGMの通し番号
	enum BGMID
	{
		Title,
		City,
		World,
		Space,
		DestroyEvent,
		UFOEvent,
		AIBurstEvent,
		Result,

		BGMMax
	};

	// Voiceの通し番号
	enum VoiceID
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

		VoiceMax
	};

	//音声ファイルのパス
	static const char* BGMPath[BGMID::BGMMax];
	static const char* VoicePath[VoiceID::VoiceMax];

	//ボイスSEの音量
	static const float VolumeVoice;
};

#endif