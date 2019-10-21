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
コンストラクタ
***************************************/
FieldEventHandler::FieldEventHandler() :
	_DestroyTown(nullptr), _GetDestoryTarget(nullptr)
{
	functerInt.resize(FuncterID_int::FuncterIntMax, nullptr);
	functerFloat.resize(FuncterID_float::FuncterFloatMax, nullptr);
	functerBool.resize(FuncterID_bool::FuncterBoolMax, nullptr);
	functerBoolReturn.resize(FuncterID_boolReturn::FuncterBoolReturnMax, nullptr);
	functerVoid.resize(FuncterID_void::FuncterVoidMax, nullptr);
}

/**************************************
デストラクタ
***************************************/
FieldEventHandler::~FieldEventHandler()
{
	functerInt.clear();
	functerFloat.clear();
	functerBool.clear();
	functerBoolReturn.clear();
}

/**************************************
AI発展レベル調整
***************************************/
void FieldEventHandler::AdjustLevelAI(float percent)
{
	functerFloat[FuncterID_float::AdjustAI](percent);
}

/**************************************
AI発展レベル加算
***************************************/
void FieldEventHandler::AddLevelAI(float num)
{
	functerFloat[FuncterID_float::AddAI](num);
}

/**************************************
街全体のリンクレベル調整
***************************************/
void FieldEventHandler::AdjustAllLinkLevel(int num)
{
	functerInt[FuncterID_int::AdjustLinkAll](num);
}

/**************************************
街一つのリンクレベル調整
***************************************/
void FieldEventHandler::AdjustLinkLevel(int num)
{
	functerInt[FuncterID_int::AdjustLink](num);
}

/**************************************
ストック数加算
***************************************/
void FieldEventHandler::AddStockNum(int num)
{
	functerInt[FuncterID_int::AddStock](num);
}

/**************************************
発展ボーナス設定
***************************************/
void FieldEventHandler::SetDevelopBonus(float percent)
{
	functerFloat[FuncterID_float::SetDevBonus](percent);
}

/**************************************
新しい街生成
***************************************/
void FieldEventHandler::CreateNewTown()
{
	functerVoid[FuncterID_void::Create]();
}

/**************************************
街破壊処理
***************************************/
void FieldEventHandler::DestroyTown(const Field::Model::PlaceModel * place)
{
	_DestroyTown(place);
}

/**************************************
操作反転処理
***************************************/
void FieldEventHandler::ReverseOperation(bool isReverse)
{
	functerBool[FuncterID_bool::ReverseOpe](isReverse);
}

/**************************************
ストック封印処理
***************************************/
void FieldEventHandler::SealUsingItem(bool isSeal)
{
	functerBool[FuncterID_bool::SealItem](isSeal);
}

/**************************************
混雑度調整処理
***************************************/
void FieldEventHandler::AdjustTrafficJam(float bias)
{
	functerFloat[FuncterID_float::AdjustTraffic](bias);
}

/**************************************
制限時間回復処理
***************************************/
void FieldEventHandler::AddRemainTime(int frame)
{
	functerInt[FuncterID_int::AddTime](frame);
}

/**************************************
地球防衛軍が使えるか
***************************************/
bool FieldEventHandler::TryUsingEDF()
{
	return functerBoolReturn[FuncterID_boolReturn::TryEDF]();
}

/**************************************
保険を使えるか
***************************************/
bool FieldEventHandler::TryUsingInsurance()
{
	return functerBoolReturn[FuncterID_boolReturn::TryInsurance]();
}

/**************************************
ゲーム進行停止
***************************************/
void FieldEventHandler::PauseGame()
{
	functerVoid[FuncterID_void::Pause]();
}

/**************************************
ゲーム進行再開
***************************************/
void FieldEventHandler::ResumeGame()
{
	functerVoid[FuncterID_void::Resume]();
}

/**************************************
破壊対象取得処理
***************************************/
const Field::Model::PlaceModel * FieldEventHandler::GetDestroyTarget()
{
	return _GetDestoryTarget();
}
