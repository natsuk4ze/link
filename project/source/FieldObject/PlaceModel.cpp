//=====================================
//
// プレイスモデル[PlaceModel.cpp]
// 機能：フィールド上に設置される3Dオブジェクトを管理するクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlaceModel.h"
#include "PlaceActor.h"

using namespace std;

//=====================================
// コンストラクタ
//=====================================
PlaceModel::PlaceModel()
{
	actor.reserve(10000);
}

//=====================================
// デストラクタ
//=====================================
PlaceModel::~PlaceModel()
{
	for (auto &a : actor)
	{
		SAFE_DELETE(a);
	}
	actor.clear();
	template <class T> vtTemp.swap(actor);
}

//=====================================
// 更新
//=====================================
void PlaceModel::Update()
{
	for (auto &a : actor)
	{
		a->Update();
	}
}

//=====================================
// 描画
//=====================================
void PlaceModel::Draw()
{
	for (auto &a : actor)
	{
		a->Draw();
	}
}