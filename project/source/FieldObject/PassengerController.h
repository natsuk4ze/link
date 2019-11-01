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
	//コンストラクタで道沿いモデルへのコールバックを渡す
	PassengerController();
	~PassengerController();

	// 更新、描画
	void Update();
	void Draw();

	// パッセンジャーセット
	void SetPassenger(std::vector<D3DXVECTOR3>& root);

	//パッセンジャーがプレイスに到達した際のコールバックが設定される
	void SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback);

private:
	std::vector<PassengerModel*> modelVector;

	std::function<void(const D3DXVECTOR3&)> callback;

	static const int PassengerReserve;
};


#endif
