//=====================================
//
//フィールイベントハンドラ処理[FieldEventHandler.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldEventHandler.h"

/**************************************
グローバル変数
***************************************/

/**************************************

***************************************/
FieldEventHandler::FieldEventHandler()
{
}

/**************************************

***************************************/
FieldEventHandler::~FieldEventHandler()
{
}

/**************************************

***************************************/
void FieldEventHandler::AdjustLevelAI(float percent)
{
}

/**************************************

***************************************/
void FieldEventHandler::AddLevelAI(float num)
{
}

/**************************************

***************************************/
void FieldEventHandler::AdjustAllLinkLevel(int num)
{
}

/**************************************

***************************************/
void FieldEventHandler::AdjustLinkLevel(int num)
{
}

/**************************************

***************************************/
void FieldEventHandler::AddStockNum(int num)
{
}

/**************************************

***************************************/
void FieldEventHandler::SetDevelopBonus(float percent)
{
}

/**************************************

***************************************/
void FieldEventHandler::CreateNewTown()
{
}

/**************************************

***************************************/
void FieldEventHandler::DestroyTown(const Field::Model::PlaceModel * place)
{
}

/**************************************

***************************************/
void FieldEventHandler::ReverseOperation(bool isReverse)
{
}

/**************************************

***************************************/
void FieldEventHandler::SealUsingItem(bool isSeal)
{
}

/**************************************

***************************************/
void FieldEventHandler::RaiseTrafficJam(float bias)
{
}

/**************************************

***************************************/
void FieldEventHandler::RecoveryRemainTime(int frame)
{
}

/**************************************

***************************************/
bool FieldEventHandler::TryUsingEDF()
{
	return false;
}

/**************************************

***************************************/
bool FieldEventHandler::TryUsingInsurance()
{
	return false;
}

/**************************************

***************************************/
void FieldEventHandler::PauseGame()
{
}

/**************************************

***************************************/
void FieldEventHandler::ResumeGame()
{
}

/**************************************

***************************************/
const Field::Model::PlaceModel * FieldEventHandler::GetDestroyTarget()
{
	return nullptr;
}
