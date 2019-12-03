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

	Debug::Begin("RewardCheck");
	Debug::Text("ButtonMashing %s", RewardController::Instance()->CheckAchieved(RC::Type::ButtonMashing) ? "true" : "false");
	Debug::Text("Destructer %s", RewardController::Instance()->CheckAchieved(RC::Type::Destructer) ? "true" : "false");
	Debug::Text("Artist %s", RewardController::Instance()->CheckAchieved(RC::Type::Artist) ? "true" : "false");
	Debug::Text("Linker %s", RewardController::Instance()->CheckAchieved(RC::Type::Linker) ? "true" : "false");
	Debug::Text("MinusMaster %s", RewardController::Instance()->CheckAchieved(RC::Type::MinusMaster) ? "true" : "false");
	Debug::Text("PlusMaster %s", RewardController::Instance()->CheckAchieved(RC::Type::PlusMaster) ? "true" : "false");
	Debug::Text("Pioneer %s", RewardController::Instance()->CheckAchieved(RC::Type::Pioneer) ? "true" : "false");
	Debug::Text("MasterAI %s", RewardController::Instance()->CheckAchieved(RC::Type::MasterAI) ? "true" : "false");
	Debug::Text("MinusComplete %s", RewardController::Instance()->CheckAchieved(RC::Type::MinusComplete) ? "true" : "false");
	Debug::Text("PlusComplete %s", RewardController::Instance()->CheckAchieved(RC::Type::PlusComplete) ? "true" : "false");
	Debug::End();
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

		if (RewardController::Instance()->CheckAchieved(RC::Type(i)))
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

