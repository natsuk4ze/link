//=====================================
//
//タスクマネージャ処理[TaskManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TaskManager.h"
#include "DelayedTask.h"
#include "PeriodicTask.h"
#include "Task.h"
#include "../Tool/DebugWindow.h"

/**************************************
マクロ定義
***************************************/

/**************************************
遅延タスク作成処理
***************************************/
TaskHandle TaskManager::CreateDelayedTask(int delay, const std::function<void(void)>& task)
{
	std::shared_ptr<DelayedTask> ptr = std::make_shared<DelayedTask>(delay, task);
	taskList.push_back(ptr);

	return TaskHandle(ptr);
}

/**************************************
定期タスク作成処理
***************************************/
TaskHandle TaskManager::CreatePeriodicTask(int interval, const std::function<void(void)>& task)
{
	std::shared_ptr<PeriodicTask> ptr = std::make_shared<PeriodicTask>(interval, task);
	taskList.push_back(ptr);

	return TaskHandle(ptr);
}

/**************************************
クリア処理
***************************************/
void TaskManager::ClearAll()
{
	taskList.clear();
}

/**************************************
TaskManager更新処理
***************************************/
void TaskManager::Update()
{
	//終了したタスクを削除
	taskList.remove_if([](std::shared_ptr<Task> task)
	{
		return task->IsFinished();
	});

	//タスク実行
	for (auto&& task : taskList)
	{
		task->Run();
	}
}

/**************************************
TaskHandleコンストラクタ
***************************************/
TaskHandle::TaskHandle()
{

}

/**************************************
TaskHandleコンストラクタ
***************************************/
TaskHandle::TaskHandle(std::shared_ptr<Task> task) :
	task(task)
{
}

/**************************************
TaskHandleデストラクタ
***************************************/
TaskHandle::~TaskHandle()
{

}

/**************************************
TaskHandle代入演算子
***************************************/
TaskHandle & TaskHandle::operator=(const TaskHandle & src)
{
	task.reset();
	task = src.task;

	return *this;
}

/**************************************
TaskHandle停止処理
***************************************/
void TaskHandle::Stop()
{
	std::shared_ptr<Task> ptr = task.lock();
	if (ptr)
	{
		ptr->Stop();
	}
}

/**************************************
TaskHandle再開処理
***************************************/
void TaskHandle::Resume()
{
	std::shared_ptr<Task> ptr = task.lock();
	if (ptr)
	{
		ptr->Resume();
	}
}

/**************************************
TaskHandle中断処理
***************************************/
void TaskHandle::Pause()
{
	std::shared_ptr<Task> ptr = task.lock();
	if (ptr)
	{
		ptr->Pause();
	}
}
