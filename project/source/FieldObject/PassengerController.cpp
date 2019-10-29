//=====================================
//
// パッセンジャーコントローラ[PassengerController.cpp]
// 機能：パッセンジャー管理クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PassengerController.h"
#include <algorithm>

//**************************************
// クラスのメンバ変数初期化
//**************************************
const int PassengerController::PassengerReserve = 1000;

//=====================================
// コンストラクタ
//=====================================
PassengerController::PassengerController()
{
	modelVector.reserve(PassengerReserve);
}

//=====================================
// デストラクタ
//=====================================
PassengerController::~PassengerController()
{
	for (auto& vec : modelVector)
	{
		SAFE_DELETE(vec);
	}
	modelVector.clear();
}

//=====================================
// 更新
//=====================================
void PassengerController::Update()
{
	for (auto& actor : modelVector)
	{
		actor->Update();
	}
}

//=====================================
// 描画
//=====================================
void PassengerController::Draw()
{
	for (auto& actor : modelVector)
	{
		actor->Draw();
	}
}

//=====================================
// パッセンジャーのセット
//=====================================
void PassengerController::SetPassenger(std::vector<D3DXVECTOR3>& root)
{
	//bool check = false;
	//// vectorの内部に未使用のものがあるか確認
	//std::any_of(modelVector.begin(), modelVector.end(), [=] 
	//{
	//	modelVector->IsActive();
	//});

	//if (check)
	//{

	//}
	//else
	//{
		PassengerModel *model = new PassengerModel(root);
		modelVector.push_back(model);
	//}
}