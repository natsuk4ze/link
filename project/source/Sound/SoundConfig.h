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

	// SEの通し番号
	enum SEID
	{
		// *** Voice ***
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

		// *** ME ***
		CreationEvent,
		FieldLevelUp,
		Finish,
		CountDown,

		// *** SE ***
		Select01,			// 決定、道終点
		Select02,			// 道始点
		Select03,			// 道始点（ドリル）
		MoveCursor,			// カーソル移動
		Fall,				// 道落下
		Beat,				// 連打
		BeatStart,			// 連打ゲームスタート
		BeatFinish,			// 連打ゲーム終了
		BeatSuccess,		// 連打ゲーム成功
		BeatFailed,			// 連打ゲーム失敗
		Transition,			// シーンチェンジ
		NewTownSE,			// 新しい町出現
		NewContinentSE,		// 新大陸出現
		NewStarSE,			// 新しい星誕生
		AIBurstSE,			// AI暴走
		Error,				// そこに道は置けません
		EventHappen,		// イベント発生
		TimeStopEventHappen,// 時間停止イベント発生
		Bom,				// 爆破
		UFO,				// UFO
		NewField,			// 新しいフィールドに遷移

		SEMax
	};

	//音声ファイルのパス
	static const char* BGMPath[BGMID::BGMMax];
	static const char* SEPath[SEID::SEMax];

	//ボイスSEの音量
	static const float VolumeVoice;

	//BGMの音量
	static const float VolumeBGM;

	static BGMID GetBgmID(int fieldLevel);
};

#endif