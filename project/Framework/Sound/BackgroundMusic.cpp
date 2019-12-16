//=====================================
//
//BackGroundMusic.cpp
//機能:BGM管理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BackGroundMusic.h"
#include "sound.h"

/**************************************
staticメンバ
***************************************/
std::unordered_map<int, MusicClip*> BGM::musicContainer;
std::vector<MusicClip::MusicState*> BGM::fsm;

/**************************************
staticメンバ
***************************************/
void BGM::Init()
{
	//ミュージッククリップのステートマシン作成
	fsm.resize(MusicClip::State::Max, NULL);
	fsm[MusicClip::Idle] = new MusicClip::MusicIdle();
	fsm[MusicClip::Fade] = new MusicClip::MusicFade();
	fsm[MusicClip::OnPlay] = new MusicClip::MusicOnPlay();
	fsm[MusicClip::OnStop] = new MusicClip::MusicOnStop();
	fsm[MusicClip::OnResume] = new MusicClip::MusicOnResume();
}

/**************************************
staticメンバ
***************************************/
void BGM::Uninit()
{
	//ステートマシン削除
	for (auto&& state : fsm)
	{
		SAFE_DELETE(state);
	}
	fsm.clear();

	Clear();
}

/**************************************
更新処理
***************************************/
void BGM::Update()
{
	for (auto&& pair : musicContainer)
	{
		MusicClip::State next = pair.second->Update();
		pair.second->ChangeState(fsm[next]);
	}
}

/**************************************
読み込み処理
***************************************/
void BGM::Load(const char * path, int tag)
{
	//重複確認
	if (musicContainer.count(tag) != 0)
		return;

	//読み込んで登録
	LPDIRECTSOUNDBUFFER8 buffer = Sound::Load(path);
	MusicClip *music = new MusicClip(buffer);
	musicContainer.emplace(tag, music);

	music->ChangeState(fsm[MusicClip::Idle]);
}

/**************************************
クリア処理
***************************************/
void BGM::Clear()
{
	//ミュージックコンテナ削除
	for (auto&& pair : musicContainer)
	{
		SAFE_DELETE(pair.second);
	}
	musicContainer.clear();
}

/**************************************
再生処理
***************************************/
void BGM::Play(int tag, float volume)
{
	//登録確認
	if (musicContainer.count(tag) == 0)
		return;

	MusicClip* music = musicContainer[tag];
	music->SetVolume(volume);
	music->ChangeState(fsm[MusicClip::OnPlay]);
}

/**************************************
停止処理
***************************************/
void BGM::Stop(int tag)
{
	//登録確認
	if (musicContainer.count(tag) == 0)
		return;

	musicContainer[tag]->ChangeState(fsm[MusicClip::OnStop]);
}

/**************************************
停止処理
***************************************/
void BGM::Stop()
{
	for (auto&& pair : musicContainer)
	{
		Stop(pair.first);
	}
}

/**************************************
再開処理
***************************************/
void BGM::Resume(int tag, float volume)
{
	//登録確認
	if (musicContainer.count(tag) == 0)
		return;

	musicContainer[tag]->SetVolume(volume);
	musicContainer[tag]->ChangeState(fsm[MusicClip::OnResume]);
}

/**************************************
再開処理
***************************************/
void BGM::Resume()
{
	for (auto&& pair : musicContainer)
	{
		Resume(pair.first);			
	}
}

/**************************************
フェードイン処理
***************************************/
void BGM::FadeIn(int tag, float volume, int duration)
{
	Play(tag, 0.0f);
	Fade(tag, volume, duration, false);
}

/**************************************
フェード処理
***************************************/
void BGM::Fade(int tag, float volume, int duration, bool flgStop)
{
	//登録確認
	if (musicContainer.count(tag) == 0)
		return;

	MusicClip *music = musicContainer[tag];
	music->SetFade(volume, duration, flgStop);
	musicContainer[tag]->ChangeState(fsm[MusicClip::Fade]);
}

/**************************************
フェード処理
***************************************/
void BGM::Fade(float volume, int duration, bool flgStop)
{
	for (auto&& pair : musicContainer)
	{
		Fade(pair.first, volume, duration, flgStop);
	}
}
