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
void InfoController::SetLinkLevel(const Field::FieldPosition& key, const int& townLevel)
{
		// 一致する要素がMap内に存在しない場合
		if (LinkInfoMap.count(key) == 0)
		{
			LinkInfoActor* link = new LinkInfoActor(key.ConvertToWorldPosition(), townLevel);
			LinkInfoMap.emplace(key, link);
		}
		// 存在する場合、レベルを更新するだけ
		else
		{
			LinkInfoMap.at(key)->SetLevel(townLevel);
		}
}