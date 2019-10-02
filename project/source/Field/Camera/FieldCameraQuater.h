//=====================================
//
//FieldCameraQuater.h
//機能:フィールドカメラクォータービュー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCAMERAQUATER_H_
#define _FIELDCAMERAQUATER_H_

#include "../../../main.h"
#include "FieldCamera.h"
#include "../../../Framework/Pattern/BaseState.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldCamera::FieldCameraQuater : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);
};
#endif