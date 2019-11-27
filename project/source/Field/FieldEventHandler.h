//=====================================
//
// FieldEventHandler.h
// 機能:フィールイベントハンドラ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDEVENTHANDLER_H_
#define _FIELDEVENTHANDLER_H_

#include "../../main.h"

#include <functional>
#include <vector>

/**************************************
前方宣言
***************************************/
namespace Field::Model
{
	class PlaceModel;
}

namespace Field
{
	class FieldController;
}

/**************************************
クラス定義
***************************************/
class FieldEventHandler
{
public:
	FieldEventHandler();
	~FieldEventHandler();

	void AdjustLevelAI(float percent);							//AI発展レベルの調整処理
	void AddLevelAI(float num);									//AI発展レベル加算処理
	void AdjustAllLinkLevel(int num);							//街全体のリンクレベル調整処理
	void AdjustLinkLevel(int num);								//街一つのリンクレベル調整処理
	void AddStockNum(int num);									//アイテムストック加算処理
	void SetDevelopBonus(float percent);						//発展度ボーナス設定処理
	void CreateNewTown(const Field::Model::PlaceModel* place);	//新しい街作成処理
	void DestroyTown(const Field::Model::PlaceModel* place);	//街破壊処理
	void CreateAtlantis(const Field::Model::PlaceModel* place);	//アトランティス出現処理
	void ReverseOperation(bool isReverse);						//操作反転処理
	void SealUsingItem(bool isSeal);							//アイテムストック封印処理
	void AdjustTrafficJam(float bias);							//混雑度調整処理
	void AddRemainTime(int frame);								//制限時間回復処理
	bool TryUsingEDF();											//地球防衛軍ストックの使用可否判定
	bool TryUsingInsurance();									//保険ストックの使用可否判定
	void PauseGame();											//ゲーム中断処理
	void ResumeGame();											//ゲーム再開処理
	const Field::Model::PlaceModel* GetDestroyTarget();			//破壊対象の街取得処理
	const Field::Model::PlaceModel* GetNewTownPosition();		//新しく街を作る予定のPlace取得
	const Field::Model::PlaceModel* GetAtlantisPlace();			//アトランティスとなるPlaceの取得
	
private:
	//float型を引数にとるファンクタの通し番号
	enum FuncterID_float
	{
		AdjustAI,
		AddAI,
		SetDevBonus,
		AdjustTraffic,
		FuncterFloatMax
	};

	//int型を引数に取るファンクタの通し番号
	enum FuncterID_int
	{
		AdjustLinkAll,
		AdjustLink,
		AddStock,
		AddTime,
		FuncterIntMax
	};

	//bool型を引数に取るファンクタの通し番号
	enum FuncterID_bool
	{
		ReverseOpe,
		SealItem,
		FuncterBoolMax
	};

	//引数を取らないboolを返すファンクタの通し番号
	enum FuncterID_boolReturn
	{
		TryEDF,
		TryInsurance,
		FuncterBoolReturnMax
	};

	//引数を取らないファンクタの通し番号
	enum FuncterID_void
	{
		Pause,
		Resume,
		FuncterVoidMax
	};

	//PlaceModelを返すファンクタの通し番号
	enum FuncterID_PlaceReturn
	{
		DestroyTarget,
		PlacePosition,
		Atlantis,
		FuncterPlaceReturnMax
	};

	//PlaceModelを引数にとるファンクタの通し番号
	enum FuncterID_Place
	{
		Destroy,
		Create,
		SetAtlantis,
		FuncterPlaceMax
	};

	std::vector<std::function<void(float)>> functerFloat;
	std::vector<std::function<void(int)>> functerInt;
	std::vector<std::function<void(bool)>> functerBool;
	std::vector<std::function<bool(void)>> functerBoolReturn;
	std::vector<std::function<void(void)>> functerVoid;
	std::vector<std::function<const Field::Model::PlaceModel*(void)>> functerPlaceReturn;
	std::vector<std::function<void(const Field::Model::PlaceModel*)>> functerPlace;
	std::function<void(bool)> SetEventControllerInPause;

	friend class GameScene;
	friend class Field::FieldController;
	friend class EventController;
};

#endif