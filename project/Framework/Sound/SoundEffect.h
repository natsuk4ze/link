//=====================================
//
//SoundEffect.h
//機能:サウンドエフェクト管理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SOUNDEFFECT_H_
#define _SOUNDEFFECT_H_

#include "../../main.h"
#include <dsound.h>
#include <unordered_map>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SE
{
public:
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

	//再生中判定
	static bool IsPlaying(int tag);

private:
	//読み込んだサウンドのコンテナ
	static std::unordered_map<int, LPDIRECTSOUNDBUFFER8> soundContainer;
};
#endif