//=====================================
//
// リワードビュアー[RewardViewer.cpp]
// 機能：各リワードを表示するクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "RewardViewer.h"
#include "RewardController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "AchieveViewer.h"

//=====================================
// コンストラクタ
//=====================================
RewardViewer::RewardViewer() :
	achieved()
{
	achieveViewer = new AchieveViewer();
}

//=====================================
// デストラクタ
//=====================================
RewardViewer::~RewardViewer()
{
	SAFE_DELETE(achieveViewer);
}

//=====================================
// 更新
//=====================================
void RewardViewer::Update()
{
	CheckAchieved();
	achieveViewer->Update();
}

//=====================================
// 描画
//=====================================
void RewardViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	achieveViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// リワード到達確認
//=====================================
void RewardViewer::CheckAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		if (achieved[i])
			continue;

		if (RewardController::Instance()->IsAchieved(RC::Type(i)))
		{
			achieved[i] = true;
			achieveViewer->SetIndex(i);
			achieveViewer->SetActive();
		}
	}
}

//=====================================
// リワード到達確認のリセット
//=====================================
void RewardViewer::ResetAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		achieved[RC::Type(i)] = false;
	}
}

