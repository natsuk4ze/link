//=====================================
//
//定期タスク処理[PeriodicTask.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PeriodicTask.h"
#include "../Math/TMath.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
PeriodicTask::PeriodicTask(int interval, const std::function<void(void)>& task) :
	Task(task),
	cntFrame(0),
	Interval(interval)
{

}

/**************************************
実行処理
***************************************/
void PeriodicTask::Run()
{
	if (state != State::Idle)
		return;

	cntFrame = Math::WrapAround(0, Interval, cntFrame + 1);

	if (cntFrame == 0)
	{
		func();
	}
}