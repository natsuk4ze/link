//=====================================
//
// ガイドカメラ[GuideCamera.h]
// 機能：ガイドウィンドウ用カメラ
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDECAMERA_H_
#define _SUIDECAMERA_H_

#include "../../../../Framework/Camera/Camera.h"

//**************************************
// クラス定義
//**************************************
class GuideCamera :
	public Camera
{
private:
public:
	GuideCamera();
	~GuideCamera();
	D3DXVECTOR3 UnProjection(const D3DXVECTOR3 & pos, float z) const override;
};

#endif