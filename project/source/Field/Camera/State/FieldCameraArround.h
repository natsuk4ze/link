//=====================================
//
// フィールドカメラアラウンド[FieldCameraArround.h]
// 機能：フィールドの中心を焦点にして回転するカメラ（タイトル、リザルト用）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _FIELDCAMERAARROUND_H_
#define _FIELDCAMERAARROUND_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseState.h"

//**************************************
// クラス定義
//**************************************
class FieldCamera::FieldCameraArround :
	public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);
};


#endif
