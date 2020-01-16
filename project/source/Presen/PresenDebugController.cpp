//=====================================
//
//PresenDebugController.cpp
//機能:プレゼン用のデバッグ操作クラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PresenDebugController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Input/Gamepad.h"
#include "../../Framework/Input/Keyboard.h"

#include "../Event/EventController.h"
#include "../Event/EventBase.h"
#include "../Event/MinusEvent/CityDestroyEvent.h"
#include "../Viewer/GameScene/Controller/EventViewer.h"

#include "../Field/FieldController.h"

/**************************************
コンストラクタ
***************************************/
PresenDebugController::PresenDebugController(GameScene * scene) :
	scene(scene)
{
}

/**************************************
デストラクタ
***************************************/
PresenDebugController::~PresenDebugController()
{
}

/**************************************
更新処理
***************************************/
void PresenDebugController::Update()
{
	return;

	//XボタンでAIレベル減少
	if (GamePad::GetTrigger(0, BUTTON_B))
	{
		_DecreaseLevelAI();
	}
	//L1ボタンで隕石召喚
	//if (GamePad::GetTrigger(0, BUTTON_Y))
	//{
	//	_RaiseMeteorEvent();
	//}
	//L2ボタンで強制レベルアップ
	if (GamePad::GetTrigger(0, BUTTON_L))
	{
		_ForceLevelUp();
	}
	//R2ボタンで強制タイムアップ
	if (GamePad::GetTrigger(0, BUTTON_R))
	{
		_ForceTimeUp();
	}

	//XボタンでAIレベル減少
	if (Keyboard::GetPress(DIK_LCONTROL) && Keyboard::GetTrigger(DIK_1))
	{
		_DecreaseLevelAI();
	}
	//L1ボタンで隕石召喚
	if (Keyboard::GetPress(DIK_LCONTROL) && Keyboard::GetTrigger(DIK_2))
	{
		_RaiseMeteorEvent();
	}
	//L2ボタンで強制レベルアップ
	if (Keyboard::GetPress(DIK_LCONTROL) && Keyboard::GetTrigger(DIK_3))
	{
		_ForceLevelUp();
	}
	//R2ボタンで強制タイムアップ
	if (Keyboard::GetPress(DIK_LCONTROL) && Keyboard::GetTrigger(DIK_4))
	{
		_ForceTimeUp();
	}

}

/**************************************
隕石イベント発生処理
***************************************/
void PresenDebugController::_RaiseMeteorEvent()
{
	if (scene->currentState != GameScene::Idle)
		return;

	EventController *controller = scene->eventController;
	EventBase *ptr = new CityDestroyEvent(controller->eventViewer, controller->beatViewer, controller->camera);

	controller->eventViewer->SetEventMessage(ptr->GetEventMessage(scene->level));
	controller->EventVec.push_back(ptr);

	scene->ChangeState(GameScene::Pause);
}

/**************************************
強制レベルアップ
***************************************/
void PresenDebugController::_ForceLevelUp()
{
	if (scene->currentState != GameScene::Idle)
		return;

	Field::FieldController *controller = scene->field;
	controller->developmentLevelAI = 9999.0f;

	//controller->SetScore();
	controller->SetResultPara();
	scene->ChangeState(GameScene::LevelUp);
}

/**************************************
AIレベル減少
***************************************/
void PresenDebugController::_DecreaseLevelAI()
{
	if (scene->currentState != GameScene::Idle)
		return;

	Field::FieldController *controller = scene->field;
	controller->developmentLevelAI = 0.0f;
}

/**************************************
強制タイムアップ
***************************************/
void PresenDebugController::_ForceTimeUp()
{
	if (scene->currentState != GameScene::Idle)
		return;

	scene->remainTime = 0;
}
