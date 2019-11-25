//=====================================
//
// セレクトカメラ[SelectCamera.h]
// 機能：セレクトウィンドウ用カメラ
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _SELECTCAMERA_H_
#define _SELECTCAMERA_H_

#include "../../../Framework/Camera/Camera.h"

//**************************************
// クラス定義
//**************************************
class SelectCamera :
	public Camera
{
public:
	SelectCamera();
	~SelectCamera();
};

#endif
