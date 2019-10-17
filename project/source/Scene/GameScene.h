//=====================================
//
//GameScene.h
//機能:ゲームシーン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include "../../Framework/Pattern/BaseState.h"
#include <vector>

// モデル表示テスト用
#include "../FieldObject/Actor/PlaceActor.h"

/**************************************
前方宣言
***************************************/
namespace Field
{
	class FieldController;
}

class SkyBox;
class FieldCamera;
class TextViewer;
class GameViewer;
class EventController;

//※イベントコントローラーが出来たらそっち移動
class EventViewer;

/**************************************
クラス定義
***************************************/
class GameScene : public BaseScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//ステートを表す列挙子
	enum State
	{
		Initialize,
		Idle,
		Max
	};

private:
	//シーンステートマシン
	std::vector<BaseState<GameScene, State>*> fsm;
	State currentState, prevState;

	SkyBox *skybox;								//背景スカイボックス
	FieldCamera* fieldCamera;					//フィールドカメラ
	Field::FieldController *field;				//フィールドコントローラ
	TextViewer *text;							//テスト用テキストビューワ
	GameViewer *gameViewer;						//ゲームビュアー

	//※イベントコントローラーが出来たらそっち移動
	EventViewer *eventViewer;


	EventController *eventController;			// イベントコントローラー
	float remainTime;							//ステージの残り時間

	//ステート遷移処理
	void ChangeState(State next);

	//各ステートクラス
	class GameInit;
	class GameIdle;

	PlaceActor* testActor;
};
#endif