//=====================================
//
//EventCamera.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EVENTCAMERA_H_
#define _EVENTCAMERA_H_

#include "../../../main.h"
#include "../../../Framework/Camera/Camera.h"

#include <functional>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class EventCamera : public Camera
{
public:
	EventCamera();
	~EventCamera();

	//初期化処理
	//イベントで使用する前にかならず呼ぶ
	void Init();

	//元のカメラを使用するように戻す
	void Restore();

	//更新処理
	void Update();

	//移動処理
	//現在の注視点を向き続けるように移動する
	void Move(const D3DXVECTOR3& position, int duration, std::function<void()> callback = nullptr);

	//平行移動処理
	//注視点も一緒に平行移動する
	void Translation(const D3DXVECTOR3& position, int duration, std::function<void()> callback = nullptr);

	//元のカメラの位置に戻す
	void Return(int duration, std::function<void()> callback = nullptr);

	//代入演算子
	EventCamera& operator=(const Camera& rhs);

private:
	//元のメインカメラ
	Camera *defaultMainCamera;

	//移動イージング用パラメータ
	int cntMove;
	int durationMove;
	D3DXVECTOR3 startPosition, endPosition;
	std::function<void()> callback;

	//注視点
	D3DXVECTOR3 referencePosition;
	bool flgLookAt;
};
#endif
