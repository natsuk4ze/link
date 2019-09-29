//=====================================
//
//テンプレートヘッダ[ObserveSubject.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _OBSEVESUBJECT_H_
#define _OBSEVESUBJECT_H_

#include <list>

/**************************************
プロトタイプ宣言
***************************************/
class BaseObserver;

/**************************************
ObserveSubjectクラス
***************************************/
class ObserveSubject
{
public:
	void AddObserver(BaseObserver *observer);
	void RemoveObserver(BaseObserver *observer);

protected:
	void NotifyObservers();

	std::list<BaseObserver*> observers;
};

#endif