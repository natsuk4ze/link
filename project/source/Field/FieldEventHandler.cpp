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
FieldEventHandler::FieldEventHandler()
{
	functerInt.resize(FuncterID_int::FuncterIntMax, nullptr);
	functerFloat.resize(FuncterID_float::FuncterFloatMax, nullptr);
	functerBool.resize(FuncterID_bool::FuncterBoolMax, nullptr);
	functerBoolReturn.resize(FuncterID_boolReturn::FuncterBoolReturnMax, nullptr);
	functerVoid.resize(FuncterID_void::FuncterVoidMax, nullptr);
	functerPlaceReturn.resize(FuncterID_PlaceReturn::FuncterPlaceReturnMax, nullptr);
	functerPlace.resize(FuncterID_Place::FuncterPlaceMax, nullptr);
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
	functerPlace.clear();
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
void FieldEventHandler::CreateNewTown(const Field::Model::PlaceModel* place)
{
	functerPlace[FuncterID_Place::Create](place);
}

/**************************************
街破壊処理
***************************************/
void FieldEventHandler::DestroyTown(const Field::Model::PlaceModel * place)
{
	functerPlace[FuncterID_Place::Destroy](place);
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
	SetEventControllerInPause(true);
}

/**************************************
ゲーム進行再開
***************************************/
void FieldEventHandler::ResumeGame()
{
	functerVoid[FuncterID_void::Resume]();
	SetEventControllerInPause(false);
}

/**************************************
破壊対象取得処理
***************************************/
const Field::Model::PlaceModel * FieldEventHandler::GetDestroyTarget()
{
	return functerPlaceReturn[FuncterID_PlaceReturn::DestroyTarget]();
}

/**************************************
新しく街を作るPlace取得処理
***************************************/
const Field::Model::PlaceModel * FieldEventHandler::GetNewTownPosition()
{
	return functerPlaceReturn[FuncterID_PlaceReturn::PlacePosition]();
}

/**************************************
アトランティスとなるPlaceの取得
***************************************/
const Field::Model::PlaceModel * FieldEventHandler::GetAtlantisPlace()
{
	return functerPlaceReturn[FuncterID_PlaceReturn::Atlantis]();
}
