//=====================================
//
//ベースオブザーバーヘッダ[BaseObserver.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEOBSERVER_H_
#define _BASEOBSERVER_H_

/**************************************
マクロ定義
***************************************/

/**************************************
前方宣言
***************************************/
class ObserveSubject;

/**************************************
BaseObserverクラス
継承先でvoid OnNotified()を定義する
***************************************/
class BaseObserver
{
public:
	virtual void OnNotified(ObserveSubject *notifier) = 0;
};

#endif