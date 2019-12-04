//=====================================
//
//SoundEffect.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SoundEffect.h"
#include "sound.h"

/**************************************
staticメンバ
***************************************/
std::unordered_map<int, LPDIRECTSOUNDBUFFER8> SE::soundContainer;
const char* SE::path[] = {
	{"data/SOUND/VOICE/AIBonus.wav"},
	{"data/SOUND/VOICE/AIOutofControll.wav"},
	{"data/SOUND/VOICE/AIOutofControllStop.wav"},
	{"data/SOUND/VOICE/AllLinkLevelUp.wav"},
	{"data/SOUND/VOICE/DevelopSpeedUp.wav"},
	{"data/SOUND/VOICE/DrillStock.wav"},
	{"data/SOUND/VOICE/LinkLevelDown.wav"},
	{"data/SOUND/VOICE/LinkLevelUp.wav"},
	{"data/SOUND/VOICE/MeteorBreakFailed.wav"},
	{"data/SOUND/VOICE/MeteorBreakSuccess.wav"},
	{"data/SOUND/VOICE/NewContinent.wav"},
	{"data/SOUND/VOICE/NewStar.wav"},
	{"data/SOUND/VOICE/NewTown.wav"},
	{"data/SOUND/VOICE/TimeLimitHeal.wav"},
	{"data/SOUND/VOICE/UMAFailed.wav"},
	{"data/SOUND/VOICE/UMAStop.wav"}
};

/**************************************
読み込み処理
***************************************/
void SE::Load(const char * path, int tag)
{
	//重複確認
	if (soundContainer.count(tag) != 0)
		return;

	soundContainer.emplace(tag, Sound::Load(path));

	//読み込みに失敗していたらアサート
	assert(soundContainer[tag]);
}

/**************************************
クリア処理
***************************************/
void SE::Clear()
{
	for (auto&& pair : soundContainer)
	{
		SAFE_RELEASE(pair.second);
	}
	soundContainer.clear();
}

/**************************************
再生処理
***************************************/
void SE::Play(int tag, float volume)
{
	//登録確認
	if (soundContainer.count(tag) == 0)
		return;

	LPDIRECTSOUNDBUFFER8 buffer = soundContainer[tag];
	Sound::SetVolume(buffer, volume);
	Sound::Play(buffer, Sound::E_DS8_FLAG_NONE, true);
}

/**************************************
停止処理
***************************************/
void SE::Stop(int tag)
{
	//登録確認
	if (soundContainer.count(tag) == 0)
		return;

	Sound::Stop(soundContainer[tag]);
}

/**************************************
停止処理
***************************************/
void SE::Stop()
{
	for (auto&& pair : soundContainer)
	{
		Sound::Stop(pair.second);
	}
}

/**************************************
再開処理
***************************************/
void SE::Resume(int tag)
{
	//登録確認
	if (soundContainer.count(tag) == 0)
		return;

	//止まっていたところから再生開始
	Sound::Play(soundContainer[tag], Sound::E_DS8_FLAG_NONE, false);
}

/**************************************
再開処理
***************************************/
void SE::Resume()
{
	for (auto&& pair : soundContainer)
	{
		Sound::Play(pair.second, Sound::E_DS8_FLAG_NONE, false);
	}
}
