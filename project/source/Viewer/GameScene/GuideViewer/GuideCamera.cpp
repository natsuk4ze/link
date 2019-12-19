//=====================================
//
// ガイドカメラ[GuideCamera.cpp]
// 機能：ガイドウィンドウ用カメラ
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideCamera.h"

#define CAMERA_HEIGHT 7.0f

//=====================================
// コンストラクタ
//=====================================
GuideCamera::GuideCamera()
{
	const float ScreenHeight = 360.0f;
	const float ScreenWidth = 360.0f;
	const float InitViewAspect = ScreenWidth / ScreenHeight;
	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, CAMERA_HEIGHT, 4.0f);
	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, CAMERA_HEIGHT, 100.0f);
	
	transform->SetPosition(InitPos);
	transform->LookAt(InitTarget);

	viewAspect = InitViewAspect;

	D3DXMatrixIdentity(&viewport);
	viewport._11 = ScreenWidth / 2.0f;
	viewport._22 = -ScreenHeight / 2.0f;
	viewport._41 = ScreenWidth / 2.0f;
	viewport._42 = ScreenHeight / 2.0f;

	//ビュー行列作成
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view,
		&InitPos,
		&InitTarget,
		&transform->Up());

	viewNear = 0.5f;
	viewFar = 500.0f;

	//プロジェクション行列作成
	D3DXMatrixIdentity(&projection);
	D3DXMatrixPerspectiveFovLH(&projection,
		viewAngle,
		viewAspect,
		viewNear,
		viewFar);

	//変換行列を計算
	VPV = view * projection * viewport;

	//逆行列を計算
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixInverse(&invProjection, NULL, &projection);
	D3DXMatrixInverse(&invVPV, NULL, &VPV);

	Set();
}

//=====================================
// デストラクタ
//=====================================
GuideCamera::~GuideCamera()
{
}

D3DXVECTOR3 GuideCamera::UnProjection(const D3DXVECTOR3 & pos, float z) const
{
	D3DXVECTOR3 out;
	D3DXVec3TransformCoord(&out, &D3DXVECTOR3(pos.x, pos.y, z), &invVPV);
	return out;
}
