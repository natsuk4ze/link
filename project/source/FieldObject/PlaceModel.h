//=====================================
//
// プレイスモデル[PlaceModel.h]
// 機能：フィールド上に設置される3Dオブジェクトを管理するクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PLACEMODEL_H_
#define _PLACEMODEL_H_

#include <vector>

//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class PlaceActor;
class PlaceModel
{
private:
	vector<PlaceActor*> actor;

public:
	PlaceActor();
	~PlaceActor();
	void Update();
	void Draw();

};

#endif

