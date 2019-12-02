//=====================================
//
// セレクトカメラ[SelectCamera.h]
// 機能：セレクトウィンドウ用カメラ
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "SelectCamera.h"

//=====================================
// コンストラクタ
//=====================================
SelectCamera::SelectCamera()
{
	const float ScreenHeight = 320.0f;
	const float ScreenWidth = 1200.0f;
	const float InitViewAspect = ScreenWidth / ScreenHeight;
	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 10.0f, -100.0f);
	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, -30.0f, 0.0f);

	transform.SetPosition(InitPos);
	transform.LookAt(InitTarget);

	viewAspect = InitViewAspect;
}

//=====================================
// デストラクタ
//=====================================
SelectCamera::~SelectCamera()
{
}
