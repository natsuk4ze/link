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
#include "PassengerActor.h"

//**************************************
// クラス定義
//**************************************
class PassengerModel
{
private:
	PassengerActor* actor;
	std::vector<D3DXVECTOR3> root;					// 出発地点から目的地までの座標を格納
	int nextDest;									// rootの添字として使用

	void CheckCallback();							// コールバックの確認

public:
	PassengerModel(const std::vector<D3DXVECTOR3>& root);
	~PassengerModel();

	// 更新、描画
	void Update();
	void Draw();
};

#endif
