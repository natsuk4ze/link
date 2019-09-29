//=====================================
//
// Delegate.h
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include <memory>

/**************************************
前方宣言
***************************************/

/**************************************
Delegater基底クラス
***************************************/
class DelegateBase
{
public:
	DelegateBase() {}
	virtual ~DelegateBase() {}

	//int型引数有り戻り値無しの関数
	virtual void operator()(int arg) = 0;
};

/**************************************
Delegaterクラス
***************************************/
template <class T>
class Delegate : public DelegateBase
{
	typedef void(T::*EventFunc)(int);
public:
	Delegate() :
		object(NULL), func(NULL) {}

	virtual ~Delegate() {}

	//引数なし戻り値なしの関数実行のオペレータ
	virtual void operator()(int arg)
	{
		//if (object != NULL && func != NULL)
			(object->*func)(arg);
	}

	//オブジェクトと関数の登録処理
	void Set(T* object, EventFunc func)
	{
		this->object = object;
		this->func = func;
	}

	//デリゲータ作成処理
	static DelegateBase* Create(T* object, void (T::*func)(int))
	{
		Delegate<T>* delegate = new Delegate<T>;
		delegate->Set(object, func);
		return  delegate;
	}

protected:
	T* object;			//オブジェクト
	EventFunc func;		//関数ポインタ
};

#endif
