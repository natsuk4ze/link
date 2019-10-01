//=====================================
//
//FIeldCamera.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FIeldCamera.h"

/**************************************
コンストラクタ
***************************************/
FieldCamera::FieldCamera()
{
	fsm.resize(Mode::Max);
}

/**************************************
デストラクタ
***************************************/
FieldCamera::~FieldCamera()
{
	Utility::DeleteContainer(fsm);
}

/**************************************
更新処理
***************************************/
void FieldCamera::Update()
{
	//追従目標の座標を視点に設定
	target = targetObject->GetPosition();

	//ステートの更新
	fsm[currentMode]->OnUpdate(*this);

	Camera::Update();
}

/**************************************
モード切替処理
***************************************/
void FieldCamera::ChangeMode()
{
	currentMode = (Mode)Math::WrapAround(Mode::QuaterView, Mode::Max, currentMode + 1);

	fsm[currentMode]->OnStart(*this);
}

/**************************************
追従目標設定処理
***************************************/
void FieldCamera::SetFollowTarget(GameObject * object)
{
	targetObject = object;
}
