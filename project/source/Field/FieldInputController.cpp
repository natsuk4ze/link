//=====================================
//
//フィールドの入力管理処理[FieldInputController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldInputController.h"
#include "../../Framework/Input/input.h"

namespace Field
{
	/**************************************
	ビルドボタンのトリガー検出
	***************************************/
	bool GetBuildTrigger()
	{
		if (Keyboard::GetTrigger(DIK_Z))
			return true;

		return false;
	}

	/**************************************
	開拓ボタンのトリガー検出
	***************************************/
	bool GetDevelopTrigger()
	{
		if (Keyboard::GetTrigger(DIK_X))
			return true;

		return false;
	}

	/**************************************
	ビルドキャンセル検出
	***************************************/
	bool GetBuildCancel()
	{
		//Xキーのトリガー入力を検出したらキャンセル
		if (Keyboard::GetTrigger(DIK_X))
			return true;

		return false;
	}

	/**************************************
	開拓キャンセル検出
	***************************************/
	bool GetDevelopCancel()
	{
		//Zキーのトリガーを検出したらキャンセル
		if (Keyboard::GetTrigger(DIK_Z))
			return true;

		return false;
	}
}


