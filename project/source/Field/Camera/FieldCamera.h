//=====================================
//
//FieldCamera.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCAMERA_H_
#define _FIELDCAMERA_H_

#include "../../../Framework/Camera/Camera.h"
#include "../../../Framework/Pattern/BaseState.h"
#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldCamera : public Camera
{
public:
	//カメラモードを表す列挙子
	enum Mode
	{
		QuaterView,				//クォータービューモード
		FarView,				//遠景モード
		AngleRotate,			//回転ステート
		TransitionOut,			//レベルアップ時の引き
		TransitionIn,			//新しいレベルになった時の初期状態
		Arround,				//フィールドの中心を焦点にして回転（タイトル、リザルト）
		Max
	};

	//コンストラクタ、デストラクタ
	FieldCamera();
	~FieldCamera();

	//更新処理
	void Update();

	//モード切替処理
	void ChangeMode(Mode next);

	//追従目標設定処理
	void SetFollowTarget(GameObject* object);

	static const int DurationRotate;
	static const float AnglePeriod;
	static const float LengthFromTarget;
	static const float InitCameraAngle;
	static const float CameraAngleY;

private:
	GameObject *targetObject;						//追従目標
	D3DXVECTOR3 startPosition, goalPosition;		//イージング用座標
	int cntFrame;									//フレームカウント

	float cameraAngle;								//カメラのXZ平面の角度
	float startAngle, endAngle;						//イージング用角度
	int cntRotate;									//回転フレームカウント

	D3DXVECTOR3 startEyeVector;						//遷移開始時の視線ベクトル

	Mode currentMode;								//現在のモード
	std::vector<BaseState<FieldCamera, Mode>*> fsm;	//ステートマシン
	
	//ステートクラス
	class FieldCameraQuater;
	class FieldCameraFar;
	class FieldCameraRotate;
	class FieldCameraTransitionOut;
	class FieldCameraTransitionIn;
	class FieldCameraArround;
};

#endif