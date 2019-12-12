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

/**************************************
前方宣言
***************************************/
namespace Field
{
	class FieldController;
	class FieldSkyBox;
}

namespace Field::Model
{
	class PlaceModel;
}

class FieldCamera;
class GameViewer;
class EventController;
class GameParticleManager;
class FieldEventHandler;
class BloomController;
class PlaceActor;
class SerialWrapper;
class UDPClient;
class SceneParticleManager;
class GuideViewer;
class ResultViewer;
class NameEntryViewer;
class TitleViewer;
class RewardNotifier;

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
		FarView,
		Title,
		Result,
		TransitionOut,
		TransitionIn,
		AchieveResult,
		Max
	};

	//ステート遷移処理
	void ChangeState(State next);

	//各レベルのターンテーブルの角度
	static const unsigned char AngleTable[];

private:
	using SceneState = BaseState<GameScene, State>;

	//シーンステートマシン
	std::vector<SceneState*> fsm;
	State currentState, prevState;

	FieldCamera* fieldCamera;					//フィールドカメラ
	Field::FieldController *field;				//フィールドコントローラ
	GameViewer *gameViewer;						//ゲームビュアー
	EventController *eventController;			//イベントコントローラー
	GameParticleManager *particleManager;		//パーティクルマネージャ
	SceneParticleManager *levelParticleManager;	//レベル個別のパーティクルマネージャ
	FieldEventHandler* eventHandler;			//イベントハンドラ
	UDPClient *Client;							//クライアント
	ResultViewer*resultViewer;					//リザルトビュアー
	NameEntryViewer *nemeEntryViewer;			//名前登録ビュアー
	TitleViewer* titleViewer;					// タイトルビュアー
	RewardNotifier* rewardNotifier;					// リワードビュアー

	int remainTime;								//制限時間

	int cntFrame;								//フレームカウンタ

	int step;									//各ステートの現在ステップ

	long long entiretyScore;					//全レベルの合計スコア

	bool debugReward;							//実績リザルト画面でデバッグを使用するか
	bool debugAchievedResult[10];				//デバッグ用の達成実績

	//ポストエフェクト関連
	BloomController *bloomController;			//ブルームエフェクトのコントローラ

	//イベントコントローラへのPlace受け渡し処理
	void OnBuildRoad(Route& route);

	//レベルアップ処理
	void OnLevelUp();

	//イベントハンドラ設定処理
	void SetEventHandler();

	//デバッグ機能
	void DebugTool();

	//フィールドレベル設定処理
	void SetFieldLevel(int level);

	//クリア処理
	void Clear();

	//static定数メンバ
	static const float BloomPower[3];
	static const float BloomThrethold[3];

	//各ステートクラス
	class GameInit;
	class GameIdle;
	class GameFinish;
	class GameLevelUp;
	class GamePause;
	class GameFarView;
	class GameWaitPopup;
	class GameTitle;
	class GameResult;
	class GameTransitionOut;
	class GameTransitionIn;
	class GameAchieveResult;

	//デバッグ用フィールドレベル
	static int level;
};
#endif