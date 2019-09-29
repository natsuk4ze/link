//=====================================
//
//オブザーブサブジェクト処理[ObserveSubject.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ObserveSubject.h"
#include "BaseObserver.h"

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
オブザーバー登録処理
***************************************/
void ObserveSubject::AddObserver(BaseObserver *observer)
{
	//重複確認
	auto checkResult = find(observers.begin(), observers.end(), observer);
	if (checkResult != observers.end())
		return;

	//登録
	observers.push_back(observer);
}

/**************************************
オブザーバー削除処理
***************************************/
void ObserveSubject::RemoveObserver(BaseObserver *observer)
{
	//登録確認
	auto checkResult = find(observers.begin(), observers.end(), observer);
	if (checkResult == observers.end())
		return;

	//削除
	observers.remove(observer);
}

/**************************************
オブザーバー通知処理
***************************************/
void ObserveSubject::NotifyObservers()
{
	for (BaseObserver *observer : observers)
	{
		observer->OnNotified(this);
	}
}
