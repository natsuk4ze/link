#include "../../main.h"
#include "sound.h"
#include <math.h>

// おまじない
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

namespace Sound
{
	// グローバル変数
	IDirectSound8 *g_pDirectSound = NULL;	// サウンドインターフェース

	// サウンドの初期化
	// hWnd:ウィンドウハンドル
	HRESULT Init(HWND hWnd)
	{
		// DirectSoundオブジェクトの作成
		if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound, NULL)))
			return E_FAIL;

		// 協調レベル設定 
		if (FAILED(g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
			return E_FAIL;

		return S_OK;
	}

	// 後片付け
	void Uninit()
	{
		if (g_pDirectSound != NULL)
		{
			g_pDirectSound->Release();
			g_pDirectSound = NULL;
		}
	}

	// サウンドのロード
	// no:サウンドナンバー（ヘッダに定義された列挙型定数）
	LPDIRECTSOUNDBUFFER8 Load(const TCHAR *path)
	{
		// MMIO = マルチメディア入出力、の略。
		LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// 曲データの総合バッファ
		LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// 曲データのバッファ
		DSBUFFERDESC buff;						// バッファ設定構造体

		HMMIO hMmio = NULL;						// MMIOハンドル
		MMIOINFO mmioInfo;						// マルチメディアデータ構造体

		MMRESULT mmRes;								// MM処理結果格納変数
		MMCKINFO riffChunk, formatChunk, dataChunk;	// チャンクデータ構造体
		DWORD size;									// データサイズ格納用
		WAVEFORMATEX pcm;							// 曲データフォーマット構造体

		LPVOID pBlock;				// セカンダリバッファのデータ書き込み先アドレス
		DWORD  dwSize;				// セカンダリバッファのサイズ

		// 1.ハンドルをもとにファイルを開く
		memset(&mmioInfo, 0, sizeof(MMIOINFO));
		hMmio = mmioOpen((LPSTR)path, &mmioInfo, MMIO_READ);
		if (!hMmio)
			return NULL;

		// 2.ファイル解析① RIFFチャンク検索
		riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// 検索キーワード
		mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// キーワードをもとに検索

		if (mmRes != MMSYSERR_NOERROR)		// 見つからなかったら異常終了
		{
			mmioClose(hMmio, 0);
			return NULL;
		}

		// 3.ファイル解析② フォーマットチャンク検索
		formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// 検索キーワード
		mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// キーワードをもとに検索

		if (mmRes != MMSYSERR_NOERROR)		// 見つからなかったら異常終了
		{
			mmioClose(hMmio, 0);
			return NULL;
		}

		size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);	// 検索情報をもとに読み込み

		if (size != formatChunk.cksize) 		// 正しく読み込めなかったら異常終了
		{
			mmioClose(hMmio, 0);
			return NULL;
		}

		mmioAscend(hMmio, &formatChunk, 0);

		// 4.ファイル解析③ データチャンク検索
		dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// 検索キーワード
		mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// キーワードをもとに検索

		if (mmRes != MMSYSERR_NOERROR) 		// 見つからなかったら異常終了
		{
			mmioClose(hMmio, 0);
			return NULL;
		}

		// 5.データ読み込み
		char *pData = new char[dataChunk.cksize];					// 必要な大きさの領域を確保して
		size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// データを読み込む

		if (size != dataChunk.cksize)  		// 正しく読み込めなかったら異常終了
		{
			delete[] pData;
			return NULL;
		}

		// 6.曲を読み込む「セカンダリバッファ」を用意
		ZeroMemory(&buff, sizeof(DSBUFFERDESC));		// まず初期化
		buff.dwSize = sizeof(DSBUFFERDESC);			// そこから各種設定
		buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
		buff.dwBufferBytes = size;
		buff.lpwfxFormat = &pcm;

		// 総合バッファを作る
		if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
			return NULL;

		// サウンドバッファを取り出す
		if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
			return NULL;

		// 取り出したら総合バッファを捨てる
		pBaseBuffer->Release();

		// 7.作られたセカンダリバッファにデータを転送
		// まずは書き込みできるようバッファをロック
		if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
			return NULL;

		memcpy(pBlock, pData, dwSize);	// データ転送
		delete[] pData;					// 元の読み込み領域を消す

		// バッファロック解除
		pBuffer->Unlock(pBlock, dwSize, 0, 0);

		// セカンダリバッファを返してようやく完了...
		return pBuffer;
	}

	// 音を鳴らす
	// pBuffer:音を鳴らしたいサウンドデータのセカンダリバッファ
	// flag   :1(E_DS8_FLAG_LOOP)ならループ再生
	void Play(LPDIRECTSOUNDBUFFER8 pBuffer, int flag, bool fromHead)
	{
		if (pBuffer == NULL)
		{
			return;
		}

		if (fromHead)
		{	// 続きから鳴らすので、最初から鳴らしたい場合はSetCurrentPosition(0)をすること
			pBuffer->SetCurrentPosition(0);
		}

		pBuffer->Play(0, 0, flag);
	}

	// 音を止める
	void Stop(LPDIRECTSOUNDBUFFER8 pBuffer)
	{
		if (pBuffer == NULL)
		{
			return;
		}

		DWORD status;

		pBuffer->GetStatus(&status);
		if (status & DSBSTATUS_PLAYING)	// 鳴っていたら
		{
			pBuffer->Stop();	// 意味的にはPauseになる。
		}
	}

	// 再生中かどうか調べる
	// pBuffer:音を鳴らしたいサウンドデータのセカンダリバッファ
	bool IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer)
	{
		if (pBuffer == NULL)
		{
			return false;
		}

		DWORD status;

		pBuffer->GetStatus(&status);
		if (status & DSBSTATUS_PLAYING)
		{
			return true;
		}
		return false;
	}

	//ボリュームの設定(volume:100 ～ 0[%])
	void SetVolume(LPDIRECTSOUNDBUFFER8 pBuffer, float volume)
	{
		if (pBuffer == NULL)
		{
			return;
		}

		//ボリュームの単位をデシベルに変換
		LONG decibel = (LONG)(2000.0f * log10(volume / 100.0f));

		if (decibel < DSBVOLUME_MIN)
		{
			decibel = DSBVOLUME_MIN;
		}
		else if (decibel > DSBVOLUME_MAX)
		{
			decibel = DSBVOLUME_MAX;
		}

		pBuffer->SetVolume(decibel);
	}
}