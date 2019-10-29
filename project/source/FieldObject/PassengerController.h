//=====================================
//
// パッセンジャーコントローラ[PassengerController.h]
// 機能：パッセンジャー管理クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PASSENGERCONTROLLER_H_
#define _PASSENGERCONTROLLER_H_

#include "Passenger/PassengerModel.h"
#include <vector>
#include <functional>

//**************************************
// クラス定義
//**************************************
class PassengerController
{
public:
	PassengerController();
	~PassengerController();

	// 更新、描画
	void Update();
	void Draw();

	// パッセンジャーセット
	void SetPassenger(std::vector<D3DXVECTOR3>& root);

private:
	std::vector<PassengerModel*> modelVector;

	static const int PassengerReserve;
};


#endif
