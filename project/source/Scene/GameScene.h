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
class GameViewer;
class EventController;
class GameParticleManager;
class FieldEventHandler;
class BloomController;

/**************************************
クラス定義
***************************************/
class GameScene : public BaseScene
{
	using BaseScene::BaseScene;
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
		LevelUp,
		Pause,
		Max
	};

	//ステート遷移処理
	void ChangeState(State next);

private:
	using SceneState = BaseState<GameScene, State>;

	//シーンステートマシン
	std::vector<SceneState*> fsm;
	State currentState, prevState;

	SkyBox *skybox;								//背景スカイボックス
	FieldCamera* fieldCamera;					//フィールドカメラ
	Field::FieldController *field;				//フィールドコントローラ
	GameViewer *gameViewer;						//ゲームビュアー
	EventController *eventController;			//イベントコントローラー
	GameParticleManager *particleManager;		//パーティクルマネージャ
	FieldEventHandler* eventHandler;			//イベントハンドラ

	int remainTime;								//制限時間

	//ポストエフェクト関連
	BloomController *bloomController;			//ブルームエフェクトのコントローラ

	//デリゲータ
	Delegate<void(Route&)> *onBuildRoad;		//道を生成したときのデリゲータ

	//イベントコントローラへのPlace受け渡し処理
	void OnBuildRoad(Route& route);

	//レベルアップ処理
	void OnLevelUp();

	//イベントハンドラ設定処理
	void SetEventHandler();

	//static定数メンバ
	static const float BloomPower[3];
	static const float BloomThrethold[3];

	//各ステートクラス
	class GameInit;
	class GameIdle;
	class GameFinish;
	class GameLevelUp;
	class GamePause;

	PlaceActor* testActor;

	//デバッグ用フィールドレベル
	static int level;
};
#endif