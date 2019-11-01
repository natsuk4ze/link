//=====================================
//
// パッセンジャーモデル[PassengerModel.h]
// 機能：パッセンジャーのモデルクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PASSENGERMODEL_H_
#define _PASSENGERMODEL_H_

#include <vector>
#include <deque>

#include "PassengerActor.h"

//**************************************
// クラス定義
//**************************************
class PassengerModel
{
private:
	PassengerActor* actor;
	std::deque<D3DXVECTOR3> route;					// 出発地点から目的地までの座標を格納
	int current;									// 
	int nextDest;									// rootの添字として使用

	void CheckCallback();							// コールバックの確認

	std::function<void(const D3DXVECTOR3&)> *callbackToAlong;

public:
	PassengerModel(const std::deque<D3DXVECTOR3>& root, std::function<void(const D3DXVECTOR3&)> *callback);
	~PassengerModel();

	// 更新、描画
	void Update();
	void Draw();

	// 使用中確認
	bool IsActive();

	// アクターのセット
	void SetActor(const std::deque<D3DXVECTOR3>& root);

	D3DXVECTOR3 FindDestination();
};

#endif
