//=====================================
//
//SerialWrapper.cpp
//機能:シリアル通信機能ラッパークラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SerialWrapper.h"

#include <tchar.h>

/**************************************
コンストラクタ
***************************************/
SerialWrapper::SerialWrapper(int comNum)
{
	TCHAR com[10];
	_stprintf_s(com, 10, _T("COM%d"), comNum);

	//シリアルポートを開く
	comPort = CreateFile(com, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	assert(comPort != INVALID_HANDLE_VALUE);
}

/**************************************
デストラクタ
***************************************/
SerialWrapper::~SerialWrapper()
{
	//シリアルポートを閉じる
	CloseHandle(comPort);
}

/**************************************
通信開始処理
***************************************/
void SerialWrapper::Begin(unsigned long speed)
{
	DCB dcb;		//シリアルポートの構成情報が入る構造体
	GetCommState(comPort, &dcb);

	dcb.BaudRate = speed;					//速度
	dcb.ByteSize = 8;						//データ長
	dcb.Parity = NOPARITY;					//パリティ
	dcb.StopBits = ONESTOPBIT;				//ストップビット長
	dcb.fOutxCtsFlow = FALSE;				//送信時CTSフロー
	dcb.fRtsControl = RTS_CONTROL_ENABLE;	//RTSフロー

	//変更した設定値を書き込み
	SetCommState(comPort, &dcb);
}

/**************************************
送信処理
***************************************/
size_t SerialWrapper::Write(char data)
{
	char* sentData = &data;		//送信する1Byte
	DWORD numberOfPut;			//実際に送信したByte数

	//ポートへ送信
	WriteFile(comPort, sentData, 1, &numberOfPut, NULL);

	return numberOfPut;
}

/**************************************
送信処理
***************************************/
size_t SerialWrapper::Write(const char buf[], int length)
{
	DWORD lengthOfSent = length;		//送信するByte数
	DWORD numberOfPut;					//実際に送信したByte数

	//ポートへ送信
	WriteFile(comPort, buf, lengthOfSent, &numberOfPut, NULL);

	return numberOfPut;
}

/**************************************
受信バッファに溜まったByte数
***************************************/
int SerialWrapper::Available()
{
	//受信データ数を調べる
	DWORD errors;
	COMSTAT comStat;
	ClearCommError(comPort, &errors, &comStat);

	int lengthOfReceived = comStat.cbInQue;		//受信したメッセージ帳を取得

	return lengthOfReceived;
}

/**************************************
読み込み処理
***************************************/
int SerialWrapper::Read()
{
	if (Available() < 1)
		return -1;

	char buf[1];			//受信データ格納用
	DWORD numberOfRead;		//実際に受信したバイト数

	//データ受信
	bool result = ReadFile(comPort, buf, 1, &numberOfRead, NULL);

	if (result == FALSE)
	{
		return -1;
	}
	else
	{
		return buf[0];
	}
}
