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

private:
	GameObject *targetObject;						//追従目標
	D3DXVECTOR3 startPosition, goalPosition;		//イージング用座標
	int cntFrame;									//フレームカウント

	float cameraAngle;
	float startAngle, endAngle;
	int cntRotate;

	Mode currentMode;								//現在のモード
	std::vector<BaseState<FieldCamera, Mode>*> fsm;	//ステートマシン
	
	//ステートクラス
	class FieldCameraQuater;
	class FieldCameraFar;
	class FieldCameraRotate;
};

#endif