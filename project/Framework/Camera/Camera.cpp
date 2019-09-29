//=====================================
//
//カメラ処理[Camera.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Camera.h"
#include "CameraShakePlugin.h"

/**************************************
staticメンバ
***************************************/

/**************************************
コンストラクタ
***************************************/
Camera::Camera()
{
	pluginList.push_back(ShakePlugin::Instance());
}

/**************************************
初期化処理
***************************************/
void Camera::Init()
{
	//TODO:Cameraで初期化するのではなくプラグインを作成する
	const float CameraAngleXZ = D3DXToRadian(45.0f);
	const float CameraAngleY = D3DXToRadian(60.0f);
	const float CameraLength = 50.0f;

	const D3DXVECTOR3 InitPos = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	const float InitViewAngle = D3DXToRadian(60.0f);
	const float InitViewAspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	const float InitViewNear = 10.0f;
	const float InitViewFar = 50000.0f;

	transform.SetPosition(InitPos);
	target = InitTarget;
	viewAngle = InitViewAngle;
	viewAspect = InitViewAspect;
	viewNear = InitViewNear;
	viewFar = InitViewFar;

	D3DXMatrixIdentity(&viewport);
	viewport._11 = SCREEN_WIDTH / 2.0f;
	viewport._22 = -SCREEN_HEIGHT / 2.0f;
	viewport._41 = SCREEN_WIDTH / 2.0f;
	viewport._42 = SCREEN_HEIGHT / 2.0f;

	D3DXMatrixInverse(&invVPV, NULL, &VPV);

	Set();
}

/**************************************
セット処理
***************************************/
void Camera::Set()
{
	//作業領域に現在のパラメータを設定
	eyeWork = transform.GetPosition();
	targetWork = target;
	upWork = transform.Up();

	//プラグイン反映
	for (auto& plugin : pluginList)
	{
		plugin->Apply(*this);
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビュー行列作成
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view,
		&eyeWork,
		&targetWork,
		&upWork);

	//ビュー行列設定
	pDevice->SetTransform(D3DTS_VIEW, &view);

	//プロジェクション行列作成
	D3DXMatrixIdentity(&projection);
	D3DXMatrixPerspectiveFovLH(&projection,
		viewAngle,
		viewAspect,
		viewNear,
		viewFar);

	//プロジェクション行列設定
	pDevice->SetTransform(D3DTS_PROJECTION, &projection);

	//変換行列を計算
	VPV = view * projection * viewport;

	//逆行列を計算
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixInverse(&invProjection, NULL, &projection);
	D3DXMatrixInverse(&invVPV, NULL, &VPV);
}

/**************************************
更新処理
***************************************/
void Camera::Update()
{
	//各プラグイン更新
	for (auto& plugin : pluginList)
	{
		plugin->Update();
	}
}

/**************************************
スクリーン投影処理
***************************************/
void Camera::Projection(D3DXVECTOR3& out, const D3DXVECTOR3& pos)
{
	D3DXVec3TransformCoord(&out, &pos, &mInstance->VPV);
}

/**************************************
スクリーン逆投影処理
***************************************/
void Camera::UnProjection(D3DXVECTOR3& out, const D3DXVECTOR3& pos, float z)
{
	D3DXVec3TransformCoord(&out, &D3DXVECTOR3(pos.x, pos.y, z), &mInstance->invVPV);
}

/**************************************
スクリーン逆投影処理
***************************************/
D3DXMATRIX Camera::GetViewMtx()
{
	return mInstance->view;
}

/**************************************
スクリーン逆投影処理
***************************************/
D3DXMATRIX Camera::GetInverseViewMtx()
{
	return mInstance->invView;
}

/**************************************
スクリーン逆投影処理
***************************************/
D3DXMATRIX Camera::GetProjectionMtx()
{
	return mInstance->projection;
}

