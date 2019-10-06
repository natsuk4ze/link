//=====================================
//
// FieldInputController.h
// 機能:フィールドの入力管理
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDINPUTCONTROLLER_H_
#define _FIELDINPUTCONTROLLER_H_

#include "../../main.h"

namespace Field
{
	//ルート建設開始の入力処理
	bool GetBuildTrigger();

	//開拓開始の入力処理
	bool GetDevelopTrigger();

	//ルート建設キャンセルの入力処理
	bool GetBuildCancel();

	//開拓キャンセルの入力処理
	bool GetDevelopCancel();
}

#endif