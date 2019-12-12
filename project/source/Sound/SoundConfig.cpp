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

const char* SoundConfig::VoicePath[VoiceID::VoiceMax]
{
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
	{"data/SOUND/VOICE/robo/UMAStop.wav"}
};

const float SoundConfig::VolumeVoice = 1.0f;

/**************************************
プロトタイプ宣言
***************************************/

