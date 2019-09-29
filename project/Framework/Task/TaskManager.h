//=====================================
//
//タスクマネージャヘッダ[TaskManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_

#include "../Pattern/BaseSingleton.h"

#include <functional>
#include <memory>
#include <list>

/**************************************
前方宣言
***************************************/
class Task;
class DelayedTask;
class PeriodicTask;
class TaskHandle;

/**************************************
TaskManagerクラス
***************************************/
class TaskManager : public BaseSingleton<TaskManager>
{
	friend class BaseGame;		//Update()の呼び出しをBaseGameのみに許可したいため
public:
	//遅延タスク作成処理
	std::unique_ptr<TaskHandle> CreateDelayedTask(int delay, const std::function<void(void)>& task);

	//定期タスク作成処理
	std::unique_ptr<TaskHandle> CreatePeriodicTask(int interval, const std::function<void(void)>& task);

private:
	//更新処理
	void Update();

	//タスクリスト
	std::list<std::shared_ptr<Task>> taskList;
};

/**************************************
TaskInterfaceクラス
生成した側はこのクラスを通してタスクを操作する
***************************************/
class TaskHandle
{
public:
	//コンストラクタ、デストラクタ
	TaskHandle();
	TaskHandle(std::shared_ptr<Task>);
	~TaskHandle();

	//代入演算子
	TaskHandle& operator =(const TaskHandle&);

	void Stop();		//停止処理
	void Resume();		//再開処理（一度停止したタスクは再開できない）
	void Pause();		//中断処理

private:
	std::weak_ptr<Task> task;
};
#endif