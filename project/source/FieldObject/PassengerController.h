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
	//海なのか陸なのか
	enum Geography
	{
		Ground,
		Sea
	};

	//コンストラクタで道沿いモデルへのコールバックを渡す
	PassengerController(Field::FieldLevel level);
	~PassengerController();

	// 更新、描画
	void Update();
	void Draw();

	// リソース読み込み
	void LoadResource();

	// CSV読み込み
	void LoadCSV(const char* path);

	// パッセンジャーセット
	void SetPassenger(std::deque<D3DXVECTOR3>& root);

	//パッセンジャーがプレイスに到達した際のコールバックが設定される
	void SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback);

	// PlaceActorに合わせてパッセンジャーの種類を切り替え（FieldLevel = Worldでのみ使用）
	void CheckPassengerMesh();

	// 陸or海のデータが書き換わった場合こちらを呼び出す
	void RewriteMap(const Field::FieldPosition& pos, const Geography& data);

private:
	std::vector<PassengerModel*> modelVector;
	std::function<void(const D3DXVECTOR3&)> callback;
	std::map<Field::FieldPosition, int> continentMap;	// 陸or海判別用マップ（FieldLevel = Worldでのみ使用）
	int mapRowMax;
	int mapColumMax;
	Field::FieldLevel currentLevel;
	bool initializedMap;

	static const int PassengerReserve;

};


#endif
