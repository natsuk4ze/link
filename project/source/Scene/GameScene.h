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
#include "../../Framework/Pattern/Delegate.h"

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

namespace Field::Model
{
	class PlaceModel;
}

class SkyBox;
class FieldCamera;
class TextViewer;
class GameViewer;
class EventController;

/**************************************
クラス定義
***************************************/
class GameScene : public BaseScene
{
public:
	using Route = std::vector<Field::Model::PlaceModel*>;

	void Init();
	void Uninit();
	void Update();
	void Draw();

	//ステートを表す列挙子
	enum State
	{
		Initialize,
		Idle,
		Finish,
		Max
	};

private:
	using SceneState = BaseState<GameScene, State>;

	//シーンステートマシン
	std::vector<SceneState*> fsm;
	State currentState, prevState;

	SkyBox *skybox;								//背景スカイボックス
	FieldCamera* fieldCamera;					//フィールドカメラ
	Field::FieldController *field;				//フィールドコントローラ
	TextViewer *text;							//テスト用テキストビューワ
	GameViewer *gameViewer;						//ゲームビュアー
	EventController *eventController;			//イベントコントローラー

	float remainTime;							//ステージの残り時間

	//デリゲータ
	DelegatePtr<Route&> onBuildRoad;	//道を生成したときのデリゲータ

	//ステート遷移処理
	void ChangeState(State next);

	//イベントコントローラへのPlace受け渡し処理
	void OnBuildRoad(Route& route);

	//各ステートクラス
	class GameInit;
	class GameIdle;
	class GameFinish;

	PlaceActor* testActor;
};
#endif