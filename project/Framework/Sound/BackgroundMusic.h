//=====================================
//
//BackgroundMusic.h
//機能:BGM管理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BACKGROUNDMUSIC_H_
#define _BACKGROUNDMUSIC_H_

#include "../../main.h"
#include "MusicClip.h"

#include <unordered_map>
#include <vector>
#include <dsound.h>

/**************************************
前方宣言
***************************************/

/**************************************
BGMクラス
***************************************/
class BGM
{
public:
	static void Init();
	static void Uninit();
	static void Update();

	//サウンド読み込み処理
	static void Load(const char* path, int tag);

	//読み込んだサウンドをクリアする処理
	static void Clear();

	//再生処理
	//ボリュームは1.0f ~ 0.0f
	static void Play(int tag, float volume);

	//停止処理
	static void Stop(int tag);
	static void Stop();

	//再開処理
	static void Resume(int tag);
	static void Resume();

	//フェードイン、フェードアウト
	static void FadeIn(int tag, float volume, int duration);
	static void Fade(int tag, float volume, int duration, bool flgStop);
	static void Fade(float volume, int duration, bool flgStop);

private:
	//読み込んだサウンドのコンテナ
	static std::unordered_map<int, MusicClip*> musicContainer;

	//MusicClipのステートマシン
	static std::vector<MusicClip::MusicState*> fsm;
};

#endif