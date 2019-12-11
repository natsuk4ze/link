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
}

//=====================================
// フェードアウト
//=====================================
void PlayBGM::FadeOut(SoundConfig::BGMID tag, float volume, bool flagStop)
{
	BGM::Fade(tag, volume, flagStop);
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
}
