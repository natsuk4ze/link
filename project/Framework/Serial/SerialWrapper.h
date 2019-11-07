//=====================================
//
//SerialWrapper.h
//機能:シリアル通信機能のラッパークラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SERIALWRAPPER_H_
#define _SERIALWRAPPER_H_

#include "../../main.h"

/**************************************
クラス定義
***************************************/
class SerialWrapper
{
public:
	//コンストラクタ
	//comNum : 開くCOMポートの番号
	SerialWrapper(int comNum);

	//デストラクタ
	~SerialWrapper();

	//シリアル通信の初期化
	//spped : 伝送速度
	void Begin(unsigned long speed);

	//1Byteのデータを送信する
	//char data : 送信する1Byteデータ
	virtual size_t Write(char data);

	//複数Byteのデータを送信する
	//const char buf[] : 送信データ列
	//int length : 送信データ数
	virtual size_t Write(const char buf[], int length);

	//受信バッファに溜まったByte数を返す
	virtual int Available();

	//受信バッファから1Byte読み込む
	virtual int Read();

private:
	HANDLE comPort;
};

#endif