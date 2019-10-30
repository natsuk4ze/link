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
PassengerController::PassengerController() :
	callback(nullptr)
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
	bool check = false;
	int sub = 0;
	// vectorの内部に未使用のものがあるか確認
	for (auto& vec : modelVector)
	{
		if (!vec->IsActive())
		{
			check = true;
			break;
		}
		sub++;
	}

	if (check)
	{
		modelVector[sub]->SetActor(root);
	}
	else
	{
		PassengerModel *model = new PassengerModel(root, &callback);
		modelVector.push_back(model);
	}
}

//=====================================
// コールバック設定処理
//=====================================
void PassengerController::SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback)
{
	this->callback = callback;
}
