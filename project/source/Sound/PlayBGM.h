//=====================================
//
// プレイBGM[PlayBGM.h]
// 機能：BGM再生用クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PLAYBGM_H_
#define _PLAYBGM_H_

#include "../../Framework/Pattern/BaseSingleton.h"
#include "SoundConfig.h"

//**************************************
// クラス定義
//**************************************
class PlayBGM :
	public BaseSingleton<PlayBGM>
{
	friend class BaseSingleton<PlayBGM>;
public:
	// フェードイン、フェードアウト
	void FadeIn(SoundConfig::BGMID tag, float volume, int duration, bool isResume = true);
	void FadeOut(SoundConfig::BGMID tag, float volume, int duration, bool flagStop);
	void FadeOut();

	// 一時停止、再生再開
	void Pause(SoundConfig::BGMID tag);
	void Pause();
	void Resume(SoundConfig::BGMID tag);
	
	// 直前に再生していたBGMを一時停止から復帰させる
	void ResumePrev();

private:
	PlayBGM(){}
	~PlayBGM(){}

	SoundConfig::BGMID current;		//現在のBGM
	SoundConfig::BGMID prev;		//1つ前のBGM
};

#endif
