//=====================================
//
// CameraTranslationPlugin.h
// 機能:カメラを平行移動させるプラグイン
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CAMERAMOVEPLUGIN_H_
#define _CAMERAMOVEPLUGIN_H_

#include "../../main.h"
#include "Camera.h"
#include "../Pattern/BaseSingleton.h"

/**************************************
クラス定義
***************************************/
class Camera::TranslationPlugin : public BaseCameraPlugin, public BaseSingleton<TranslationPlugin>
{
public:
	//初期化処理
	void Init();

	//更新処理
	void Update();

	//プラグイン適用処理
	void Apply(Camera& camera);

	//移動開始処理
	//引数 position : 移動先のカメラ注視点
	//引数 duration : 移動にかけるフレーム数
	void Move(const D3DXVECTOR3& position, int duration);

	//移動前の位置へ戻す処理
	//引数 duration : 移動にかけるフレーム数
	void Restore(int duration);

private:
	enum State
	{
		MoveTowards,
		RestoreBase,
		Idle
	};

	int cntFrame;					//フレームカウント
	int durationMove;				//移動時間
	D3DXVECTOR3 targetPosition;		//移動先の目標座標
	State state;					//現在のステート
};

#endif