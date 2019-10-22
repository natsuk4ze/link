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
Delegater基底クラス宣言
***************************************/
template<class TFunc>
class Delegate;

/**************************************
Delegater基底クラス定義
***************************************/
template<class TResult, class ...TArgs>
class Delegate<TResult(TArgs...)>
{
public:
	Delegate() {}
	virtual ~Delegate() {}

	virtual TResult operator()(TArgs... args) = 0;
};

/**************************************
Delegaterクラス
***************************************/
template<class TObject, class TFunc>
class DelegateObject;

template <class TObject, class TResult, class ...TArgs>
class DelegateObject<TObject, TResult(TArgs...)> : public Delegate<TResult(TArgs...)>
{
	typedef TResult(TObject::*EventFunc)(TArgs...);
public:
	DelegateObject() :
		object(NULL), func(NULL) {}

	virtual ~DelegateObject() {}

	//関数実行のオペレータ
	virtual TResult operator()(TArgs... args)
	{
		return (object->*func)(args...);
	}

	//オブジェクトと関数の登録処理
	void Set(TObject* object, EventFunc func)
	{
		this->object = object;
		this->func = func;
	}

	//デリゲータ作成処理
	static Delegate<TResult(TArgs...)>* Create(TObject* object, TResult(TObject::*func)(TArgs...))
	{
		DelegateObject<TObject, TResult(TArgs...)>* delegate = new DelegateObject<TObject, TResult(TArgs...)>;
		delegate->Set(object, func);
		return  delegate;
	}

protected:
	TObject *object;			//オブジェクト
	EventFunc func;			//関数ポインタ
};

#endif
