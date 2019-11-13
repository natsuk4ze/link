//=====================================
//
//MusicClip.h
//機能:ミュージックデータを纏めるクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MUSICCLIP_H_
#define _MUSICCLIP_H_

#include "../../main.h"
#include "../Pattern/BaseState.h"

#include <dsound.h>

/**************************************
MusicClipクラス
***************************************/
class MusicClip
{
public:
	//ステート列挙子
	enum State
	{
		Idle,
		Fade,
		OnPlay,
		OnStop,
		OnResume,
		Max
	};

	//ステートクラスの前方宣言
	class MusicIdle;
	class MusicFade;
	class MusicOnPlay;
	class MusicOnStop;
	class MusicOnResume;

	//ステートクラスの型エイリアス
	using MusicState = BaseState<MusicClip, State>;

	//コンストラクタ、デストラクタ
	MusicClip(LPDIRECTSOUNDBUFFER8 buffer);
	~MusicClip();

	//更新処理
	State Update();
	
	//ステート遷移処理
	void ChangeState(MusicState* next);

	//フェードパラメータセット処理
	void SetFade(float volume, int duration, bool isFadeOut);

	//ボリュームセット処理
	void SetVolume(float volume);

private:
	LPDIRECTSOUNDBUFFER8 buffer;		//サウンドバッファ
	float volume;						//現在のボリューム
	float targetVolume;					//目標ボリューム
	float startVolume;					//開始時のボリューム
	int cntFrame;						//フレームカウント
	int fadeDuration;					//フェードにかけるフレーム
	bool isPlaying;						//再生中かどうか
	MusicState *state;					//現在のステートクラス
	MusicState *prev;					//以前のステートクラス
};

/**************************************
MusicIdleクラス
***************************************/
class MusicClip::MusicIdle : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};

/**************************************
MusicFadeInクラス
***************************************/
class MusicClip::MusicFade : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};

/**************************************
MusicOnPlayクラス
***************************************/
class MusicClip::MusicOnPlay : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};

/**************************************
MusicOnStopクラス
***************************************/
class MusicClip::MusicOnStop : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};

/**************************************
MusicOnResumeクラス
***************************************/
class MusicClip::MusicOnResume : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};
#endif