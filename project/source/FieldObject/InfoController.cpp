//=====================================
//
// インフォコントローラ[InfoController.cpp]
// 機能：InfoActorのコントローラクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "InfoController.h"

//=====================================
// コンストラクタ
//=====================================
InfoController::InfoController()
{
	
}

//=====================================
// デストラクタ
//=====================================
InfoController::~InfoController()
{
	for (auto& map : LinkInfoMap)
	{
		SAFE_DELETE(map.second);
	}
	LinkInfoMap.clear();
}

//=====================================
// 更新
//=====================================
void InfoController::Update()
{
	for (auto& map : LinkInfoMap)
	{
		map.second->Update();
	}
}

//=====================================
// 描画
//=====================================
void InfoController::Draw()
{
	for (auto& map : LinkInfoMap)
	{
		map.second->Draw();
	}
}

//=====================================
// 町リンクレベルのセット、レベルアップ
//=====================================
void InfoController::SetLinkLevel(const Field::Model::PlaceData& data)
{
		// 一致する要素がMap内に存在しない場合
		if (LinkInfoMap.count(data.key) == 0)
		{
			LinkInfoActor* link = new LinkInfoActor(data.key.ConvertToWorldPosition(), data.townLevel);
			LinkInfoMap.emplace(data.key, link);
		}
		// 存在する場合、レベルを更新するだけ
		else
		{
			LinkInfoMap.at(data.key)->SetLevel(data.townLevel);
		}
}