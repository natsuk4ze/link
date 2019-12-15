//=====================================
//
//サウンド設定処理[SoundConfig.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "SoundConfig.h"

/**************************************
staticメンバ
***************************************/
const char* SoundConfig::BGMPath[BGMID::BGMMax]
{
	{"data/SOUND/BGM/MusMus-BGM-052.wav"},
	{"data/SOUND/BGM/MusMus-BGM-067.wav"},
	{"data/SOUND/BGM/Es-STAGE1_loop.wav"},
	{"data/SOUND/BGM/Labyrinth-Of-Time_loop.wav"},
	{"data/SOUND/BGM/Battle-Forbidden_loop.wav"},
	{"data/SOUND/BGM/Battle-Noble_loop.wav"},
	{"data/SOUND/BGM/Crasher_loop.wav"},
	{"data/SOUND/BGM/MusMus-CT-NV-TT.wav"}
};

const char* SoundConfig::SEPath[SEID::SEMax]
{
	// *** Voice ***
	{"data/SOUND/VOICE/robo/AIBonus.wav"},
	{"data/SOUND/VOICE/robo/AIOutofControll.wav"},
	{"data/SOUND/VOICE/robo/AIOutofControllStop.wav"},
	{"data/SOUND/VOICE/robo/AllLinkLevelUp.wav"},
	{"data/SOUND/VOICE/robo/DevelopSpeedUp.wav"},
	{"data/SOUND/VOICE/robo/DrillStock.wav"},
	{"data/SOUND/VOICE/robo/LinkLevelDown.wav"},
	{"data/SOUND/VOICE/robo/LinkLevelUp.wav"},
	{"data/SOUND/VOICE/robo/MeteorBreakFailed.wav"},
	{"data/SOUND/VOICE/robo/MeteorBreakSuccess.wav"},
	{"data/SOUND/VOICE/robo/NewContinent.wav"},
	{"data/SOUND/VOICE/robo/NewStar.wav"},
	{"data/SOUND/VOICE/robo/NewTown.wav"},
	{"data/SOUND/VOICE/robo/TimeLimitHeal.wav"},
	{"data/SOUND/VOICE/robo/UMAFailed.wav"},
	{"data/SOUND/VOICE/robo/UMAStop.wav"},

	// *** ME ***
	{"data/SOUND/ME/MusMus-JGL-004.wav"},
	{"data/SOUND/ME/MusMus-JGL-023.wav"},
	{"data/SOUND/ME/MusMus-JGL-026.wav"},
	{"data/SOUND/ME/CountDown.wav"},

	// *** SE ***
	{"data/SOUND/SE/kettei-02.wav"},
	{"data/SOUND/SE/btn02.wav"},
	{"data/SOUND/SE/btn03.wav"},
	{"data/SOUND/SE/btn01.wav"},
	{"data/SOUND/SE/Onmtp-Impact01-1.wav"},
	{"data/SOUND/SE/punch_09.wav"},			// デュクシ
	{"data/SOUND/SE/gong-played1.wav"},
	{"data/SOUND/SE/gong-played2.wav"},
	{"data/SOUND/SE/quiz-right_02.wav"},	// ピンポンピンポーン
	{"data/SOUND/SE/quiz-wrong_02.wav"},	// ブブー
	{"data/SOUND/SE/land-the-spaceship_02.wav"},	// っすぅーーーーーおぉーーーーーん（通り過ぎる音）
	{"data/SOUND/SE/magic-electron3.wav"},
	{"data/SOUND/SE/magic-quake2.wav"},
	{"data/SOUND/SE/wind_04.wav"},			// ンゴオオオオオオオオオオオオ
	{"data/SOUND/SE/alrat_02.wav"},			// 警告
	{"data/SOUND/SE/othr11.wav"},
	{"data/SOUND/SE/se_amd05.wav"},
	{"data/SOUND/SE/chime_01.wav"},			// ピンポーン
	{"data/SOUND/SE/blast_05.wav"},			// 爆発
	{"data/SOUND/SE/fly-a-spaceship_04.wav"},	// うにょにょにょ
	{"data/SOUND/SE/eye-shine1.wav"}
};

const float SoundConfig::VolumeVoice = 1.0f;

/**************************************
プロトタイプ宣言
***************************************/

