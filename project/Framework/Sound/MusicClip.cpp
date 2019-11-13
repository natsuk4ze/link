//=====================================
//
//MusicClip.cpp
//機能:ミュージックデータを纏めるクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MusicClip.h"
#include "sound.h"
#include "../Math/Easing.h"

/**************************************
コンストラクタ
***************************************/
MusicClip::MusicClip(LPDIRECTSOUNDBUFFER8 buffer) :
	buffer(buffer),
	volume(0.0f),
	targetVolume(0.0f),
	startVolume(0.0f),
	cntFrame(0),
	fadeDuration(0),
	isPlaying(false)
{
}

/**************************************
デストラクタ
***************************************/
MusicClip::~MusicClip()
{
	SAFE_RELEASE(buffer);
}

/**************************************
更新処理
***************************************/
MusicClip::State MusicClip::Update()
{
	return state->OnUpdate(*this);
}

/**************************************
ステート遷移処理
***************************************/
void MusicClip::ChangeState(MusicState * next)
{
	if (next == state)
		return;

	prev = state;
	state = next;
	state->OnStart(*this);
}

/**************************************
フェードパラメータセット処理
***************************************/
void MusicClip::SetFade(float volume, int duration, bool isFadeOut)
{
	targetVolume = volume;
	fadeDuration = duration;
	isPlaying = !isFadeOut;
}

/**************************************
ボリュームセット処理
***************************************/
void MusicClip::SetVolume(float volume)
{
	Sound::SetVolume(buffer, volume);
}

/**************************************
アイドルステート開始処理
***************************************/
void MusicClip::MusicIdle::OnStart(MusicClip & entity)
{
	//特に何もしない
}

/**************************************
アイドルステート更新処理
***************************************/
MusicClip::State MusicClip::MusicIdle::OnUpdate(MusicClip & entity)
{
	//特に何もしない
	return MusicClip::Idle;
}

/**************************************
フェードステート開始処理
***************************************/
void MusicClip::MusicFade::OnStart(MusicClip & entity)
{
	//フレームカウントリセット
	entity.cntFrame = 0;
	entity.startVolume = entity.volume;

	if (entity.isPlaying)
		Sound::Play(entity.buffer, Sound::E_DS8_FLAG_LOOP, false);
}

/**************************************
フェードステート更新処理
***************************************/
MusicClip::State MusicClip::MusicFade::OnUpdate(MusicClip & entity)
{
	State next = MusicClip::Fade;

	//フレームをカウントしてボリュームを求める
	entity.cntFrame++;
	float t = (float)entity.cntFrame / entity.fadeDuration;

	entity.volume = Easing::EaseValue(t, entity.startVolume, entity.targetVolume, EaseType::Linear);
	Sound::SetVolume(entity.buffer, entity.volume);

	//フェード期間が終わりなら遷移
	if (entity.cntFrame == entity.fadeDuration)
	{
		next = entity.isPlaying ? MusicClip::Idle : MusicClip::OnStop;
	}

	return next;
}

/**************************************
プレイステート開始処理
***************************************/
void MusicClip::MusicOnPlay::OnStart(MusicClip & entity)
{
	//再生開始
	Sound::Play(entity.buffer, Sound::E_DS8_FLAG_LOOP, true);
	entity.isPlaying = true;
}

/**************************************
プレイステート更新処理
***************************************/
MusicClip::State MusicClip::MusicOnPlay::OnUpdate(MusicClip & entity)
{
	//何もしないのでアイドルステートへ遷移
	return MusicClip::Idle;
}

/**************************************
ストップステート開始処理
***************************************/
void MusicClip::MusicOnStop::OnStart(MusicClip & entity)
{
	//停止処理
	Sound::Stop(entity.buffer);
	entity.isPlaying = false;
}

/**************************************
ストップステート更新処理
***************************************/
MusicClip::State MusicClip::MusicOnStop::OnUpdate(MusicClip & entity)
{
	//なにもにないのでアイドルステートへ遷移
	return MusicClip::Idle;
}

/**************************************
再開ステート開始処理
***************************************/
void MusicClip::MusicOnResume::OnStart(MusicClip & entity)
{
	//再開処理
	Sound::Play(entity.buffer, Sound::E_DS8_FLAG_LOOP, false);
	entity.isPlaying = true;
	entity.state = entity.prev;
	entity.prev = this;
}

/**************************************
再開ステート更新処理
***************************************/
MusicClip::State MusicClip::MusicOnResume::OnUpdate(MusicClip & entity)
{
	//なにもにないのでアイドルステートへ遷移
	return MusicClip::Idle;
}
