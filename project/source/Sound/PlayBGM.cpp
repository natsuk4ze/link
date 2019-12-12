//=====================================
//
// プレイBGM[PlayBGM.h]
// 機能：リザルト状態
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlayBGM.h"
#include "../../Framework/Sound/BackgroundMusic.h"

//=====================================
// フェードイン
//=====================================
void PlayBGM::FadeIn(SoundConfig::BGMID tag, float volume, int duration)
{
	BGM::FadeIn(tag, volume, duration);
	current = tag;
}

//=====================================
// フェードアウト
//=====================================
void PlayBGM::FadeOut(SoundConfig::BGMID tag, float volume, int duration, bool flagStop)
{
	BGM::Fade(tag, volume, duration, flagStop);
}

//=====================================
// フェードアウト
//=====================================
void PlayBGM::FadeOut()
{
	BGM::Fade(current, 0.1f, 30, true);
}

//=====================================
// 一時停止
//=====================================
void PlayBGM::Pause(SoundConfig::BGMID tag)
{
	BGM::Stop(tag);
	prev = tag;
}

//=====================================
// 一時停止
//=====================================
void PlayBGM::Pause()
{
	BGM::Stop(current);
	prev = current;
}

//=====================================
// 再生再開
//=====================================
void PlayBGM::Resume(SoundConfig::BGMID tag)
{
	BGM::Resume(tag);
}

//=====================================
// 直前に再生していたBGMを一時停止から復帰
//=====================================
void PlayBGM::ResumePrev()
{
	BGM::Resume(prev);
	current = prev;
}
