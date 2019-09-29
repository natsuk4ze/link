//=====================================
//
//定期タスクヘッダ[PeriodicTask.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PERIODICTASK_H_
#define _PERIODICTASK_H_

#include "Task.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
PeriodicTaskクラス
***************************************/
class PeriodicTask : public Task
{
public:
	PeriodicTask(int interval, const std::function<void(void)>& task);	//コンストラクタ

private:	
	void Run();			//実行処理

	int cntFrame;		//フレームカウント
	const int Interval;	//インターバル
};

#endif