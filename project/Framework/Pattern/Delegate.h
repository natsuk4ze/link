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
Delegater基底クラス
***************************************/
template<class T>
class DelegateBase
{
public:
	DelegateBase() {}
	virtual ~DelegateBase() {}

	//int型引数有り戻り値無しの関数
	virtual void operator()(T arg = NULL) = 0;
};

template<>
class DelegateBase<void>
{
public:
	DelegateBase() {}
	virtual ~DelegateBase() {}

	//int型引数有り戻り値無しの関数
	virtual void operator()() = 0;
};

/**************************************
型エイリアス
***************************************/
template<class T>
using DelegatePtr = DelegateBase<T>*;

/**************************************
Delegaterクラス
***************************************/
template <class OBJ, class ARG>
class Delegate : public DelegateBase<ARG>
{
	typedef void(OBJ::*EventFunc)(ARG);
public:
	Delegate() :
		object(NULL), func(NULL) {}

	virtual ~Delegate() {}

	//引数なし戻り値なしの関数実行のオペレータ
	virtual void operator()(ARG arg)
	{
		//if (object != NULL && func != NULL)
			(object->*func)(arg);
	}

	//オブジェクトと関数の登録処理
	void Set(OBJ* object, EventFunc func)
	{
		this->object = object;
		this->func = func;
	}

	//デリゲータ作成処理
	static DelegatePtr<ARG> Create(OBJ* object, void (OBJ::*func)(ARG))
	{
		Delegate<OBJ, ARG>* delegate = new Delegate<OBJ, ARG>;
		delegate->Set(object, func);
		return  delegate;
	}

protected:
	OBJ* object;			//オブジェクト
	EventFunc func;			//関数ポインタ
};

#endif
