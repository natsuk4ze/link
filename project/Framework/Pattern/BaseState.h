//=============================================================================
//
// ステートインターフェースヘッダ [BaseState.h]
// Author : 立花雄太
//
//=============================================================================
#ifndef _BASESTATE_H_
#define _BASESTATE_H_

#define STATE_CONTINUOUS	(0)		//ステートを続行する
#define STATE_FINISHED		(1)		//ステートは終了した

/*****************************************************
IStateMachineクラス
継承先でOnUpdate(), OnStart()を実装する
*****************************************************/
template <class T, class ENUM>
class IState {
public:
	virtual ENUM OnUpdate(T& entity) = 0;
	virtual void OnStart(T& entity) = 0;
};

#endif