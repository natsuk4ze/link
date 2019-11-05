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
#include <deque>
#include <functional>
#include <map>
#include "../Field/Place/FieldPlaceContainer.h"

//**************************************
// クラス定義
//**************************************
class PassengerController
{
public:
	//コンストラクタで道沿いモデルへのコールバックを渡す
	PassengerController(Field::FieldLevel level);
	~PassengerController();

	// 更新、描画
	void Update();
	void Draw();

	// パッセンジャーセット
	void SetPassenger(std::deque<D3DXVECTOR3>& root);

	//パッセンジャーがプレイスに到達した際のコールバックが設定される
	void SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback);

	// PlaceActorに合わせてパッセンジャーの種類を切り替え（FieldLevel = Worldでのみ使用）
	void CheckPassengerMesh();

private:
	std::vector<PassengerModel*> modelVector;
	std::function<void(const D3DXVECTOR3&)> callback;
	std::map<Field::FieldPosition, int> continentMap;	// 陸or海判別用マップ（FieldLevel = Worldでのみ使用）
	int mapRowMax;
	int mapColumMax;
	Field::FieldLevel currentLevel;

	static const int PassengerReserve;

	// CSV読み込み
	void LoadCSV(const char* path);

};


#endif
