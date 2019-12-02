//=====================================
//
// インフォコントローラ[InfoController.cpp]
// 機能：InfoActorのコントローラクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "InfoController.h"
#include "../Reward/RewardController.h"

//=====================================
// コンストラクタ
//=====================================
InfoController::InfoController(Field::FieldLevel currentLevel)
{
	current = currentLevel;
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

	// リワードに反映
	RewardController::Instance()->SetRewardData(RewardController::Type::Linker, SearchMaxLinkLevel());
}

//=====================================
// 描画
//=====================================
void InfoController::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (auto& map : LinkInfoMap)
	{
		map.second->Draw();
	}

	device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// 町リンクレベルのセット、レベルアップ
//=====================================
void InfoController::SetLinkLevel(const Field::PlaceData& data)
{
		// 一致する要素がMap内に存在しない場合
		if (LinkInfoMap.count(data.key) == 0)
		{
			LinkInfoActor* link = new LinkInfoActor(data.key.ConvertToWorldPosition(), data.townLevel, current);
			LinkInfoMap.emplace(data.key, link);
		}
		// 存在する場合、レベルを更新するだけ
		else
		{
			LinkInfoMap.at(data.key)->SetLevel(data.townLevel);
		}
}

//=====================================
// 全ての町のリンクレベルのセット、レベルアップ
//=====================================
void InfoController::SetAllLinkLevel(const std::vector<Field::PlaceData>& vec)
{
	for (auto& v : vec)
	{
		SetLinkLevel(v);
	}
}

//=====================================
// 一番Linkレベルの高い町のレベルを調べる
//=====================================
int InfoController::SearchMaxLinkLevel()
{
	int ret = 0;
	
	for (auto& map : LinkInfoMap)
	{
		int max = map.second->GetLevel();
		if (ret < max)
		{
			ret = max;
		}
	}

	return ret;
}
