//=====================================
//
//遅延タスク処理[DelayedTask.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "DelayedTask.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
DelayedTask::DelayedTask(int delay, const std::function<void(void)>& task) :
	cntFrame(0),
	Delay(delay),
	Task(task)
{

}

/**************************************
実行処理
***************************************/
void DelayedTask::Run()
{
	if (state != State::Idle)
		return;

	cntFrame++;

	if (cntFrame == Delay)
	{
		func();
		state = State::Finished;
	}
}
