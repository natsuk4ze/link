//=====================================
//
// ガイドカメラ[GuideCamera.cpp]
// 機能：ガイドウィンドウ用カメラ
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideCamera.h"

//=====================================
// コンストラクタ
//=====================================
GuideCamera::GuideCamera()
{
	const float ScreenHeight = 360.0f;
	const float ScreenWidth = 360.0f;
	const float InitViewAspect = ScreenWidth / ScreenHeight;
	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 64.0f, -40.0f);
	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, 64.0f, 0.0f);
	
	transform.SetPosition(InitPos);
	transform.LookAt(InitTarget);

	viewAspect = InitViewAspect;
}

//=====================================
// デストラクタ
//=====================================
GuideCamera::~GuideCamera()
{
}
