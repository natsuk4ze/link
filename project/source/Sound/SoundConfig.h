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
	enum SEID : int
	{
		// *** Voice ***
		// ***** イベント関連ボイス *****
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
		Ready,					// レディ...
		// ***** ゲーム進行関連ボイス *****
		GameStart,				// ゲームスタート
		FieldLevelUp,			// フィールドレベルアップ
		NextField,				// 次のフィールドが始まる
		NewRecord,				// スコア更新
		NewReward,				// 新しく達成したリワードがある
		// ***** リワード関連ボイス *****
		ButtonMashing,			// ボタン連打イベント○回クリア
		Destructer,				// 山破壊○回
		Artist,					// 橋を架ける○個
		Linker,					// 町のリンクレベル○レベル到達
		MinusMaster,			// マイナスイベント○回
		PlusMaster,				// プラスイベント○回
		Pioneer,				// 道を○個
		MasterAI,				// AIレベル○レベルに到達
		MinusComplete,			// マイナスイベントコンプリート
		PlusComplete,			// プラスイベントコンプリート

		// *** ME ***
		CreationEventME,
		FieldLevelUpME,
		FinishME,

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
		TimeUp,				// 制限時間終了
		LinkLevelUpSE,		// リンクレベル上昇
		Morphing,			// モーフィング
		Clap,				// ランキング更新したとき拍手
		Achieve,			// ゲーム中にリワード到達を知らせる
		UFOFall,			// UFOが降りてくる
		Cancel,				// キャンセル

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