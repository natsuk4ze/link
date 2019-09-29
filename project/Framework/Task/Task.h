//=====================================
//
//タスクヘッダ[Task.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TASK_H_
#define _TASK_H_

#include <functional>

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
Taskクラス
***************************************/
class Task
{
public:
	Task(const std::function<void(void)>&);
	~Task();

	virtual void Run() = 0;		//実行処理
	virtual void Stop();		//停止処理
	virtual void Resume();		//再開処理（一度停止したタスクは再開できない）
	virtual void Pause();		//中断処理
	virtual bool IsFinished();	//終了判定

	//状態定義
	enum State
	{
		Idle,		//実行中
		Paused,		//一時停止中
		Finished	//終了済
	};

protected:
	std::function<void(void)> func;	//処理するタスク
	State state;					//現在の状態
};

#endif