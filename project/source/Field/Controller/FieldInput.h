//=====================================
//
// FieldInputController.h
// 機能:フィールドの入力管理
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDINPUTCONTROLLER_H_
#define _FIELDINPUTCONTROLLER_H_

#include "../../../main.h"
#include "../FieldController.h"

namespace Field
{
	/**************************************
	FieldInputクラス
	***************************************/
	class FieldController::FieldInput
	{
	public :
		FieldInput(FieldController *controller);
		~FieldInput();

		//ルート建設開始の入力処理
		bool GetBuildTrigger();

		//開拓開始の入力処理
		bool GetDevelopTrigger();

		//ルート建設キャンセルの入力処理
		bool GetBuildCancel();

		//開拓キャンセルの入力処理
		bool GetDevelopCancel();

		//移動入力確認
		void CheckMoveInput();

		//カメラの入力切り替え
		bool CheckSwicthCameraMode();

		//操作反転処理
		void ReverseOperate(bool isReverse);

	private:
		FieldController * entity;

		static const int InputLongWait;
		static const int InputShortWait;
		
		int cntInputRepeat;

		int directionInput;
	};
}

#endif