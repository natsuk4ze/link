//=====================================
//
// ModelViewCamera.h
// 機能:モデルビューカメラ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MODELVIEWCAMERA_H_
#define _MODELVIEWCAMERA_H_

#include "../../main.h"
#include "../../Framework/Camera/Camera.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class ModelViewCamera : public Camera
{
	using Camera::Camera;
public:
	ModelViewCamera();
	
	void Update() override;
};

#endif