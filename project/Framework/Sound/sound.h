#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

// マクロ定義
#define SOUND_VOLUME_MAX	(100.0f)		//音量最大%
#define SOUND_VOLUME_MIN	(0.0f)			//音量最小%
#define SOUND_VOLUME_INIT	(50.0f)			//初期音量

namespace Sound
{
	enum
	{	// 再生用フラグ
		E_DS8_FLAG_NONE,
		E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
		E_DS8_FLAG_MAX
	};

	HRESULT					Init(HWND hWnd);	// 初期化
	void					Uninit();			// 後片付け
	LPDIRECTSOUNDBUFFER8	Load(const TCHAR *path);	// サウンドのロード
	void					Play(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0, bool fromHead = false);	// 音ごとに再生
	void					Stop(LPDIRECTSOUNDBUFFER8 pBuffer);					// 音を止める
	bool					IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);					// 再生中かどうか
	void					SetVolume(LPDIRECTSOUNDBUFFER8 pBuffer, float volume);	// サウンドのボリューム設定関数
}
#endif