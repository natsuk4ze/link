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

//=====================================
// コンストラクタ
//=====================================
RewardViewer::RewardViewer()
{
}

//=====================================
// デストラクタ
//=====================================
RewardViewer::~RewardViewer()
{
}

//=====================================
// 更新
//=====================================
void RewardViewer::Update()
{
	Debug::Begin("RewardCheck");
	Debug::Text("ButtonMashing %s", RewardController::Instance()->CheckAchieved(RewardController::Type::ButtonMashing) ? "true" : "false");
	Debug::Text("Destructer %s", RewardController::Instance()->CheckAchieved(RewardController::Type::Destructer) ? "true" : "false");
	Debug::Text("Artist %s", RewardController::Instance()->CheckAchieved(RewardController::Type::Artist) ? "true" : "false");
	Debug::Text("Linker %s", RewardController::Instance()->CheckAchieved(RewardController::Type::Linker) ? "true" : "false");
	Debug::Text("MinusMaster %s", RewardController::Instance()->CheckAchieved(RewardController::Type::MinusMaster) ? "true" : "false");
	Debug::Text("PlusMaster %s", RewardController::Instance()->CheckAchieved(RewardController::Type::PlusMaster) ? "true" : "false");
	Debug::Text("Pioneer %s", RewardController::Instance()->CheckAchieved(RewardController::Type::Pioneer) ? "true" : "false");
	Debug::Text("MasterAI %s", RewardController::Instance()->CheckAchieved(RewardController::Type::MasterAI) ? "true" : "false");
	Debug::Text("MinusComplete %s", RewardController::Instance()->CheckAchieved(RewardController::Type::MinusComplete) ? "true" : "false");
	Debug::Text("PlusComplete %s", RewardController::Instance()->CheckAchieved(RewardController::Type::PlusComplete) ? "true" : "false");
	Debug::End();
}

//=====================================
// 描画
//=====================================
void RewardViewer::Draw()
{
}

