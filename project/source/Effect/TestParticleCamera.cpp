//=====================================
//
//パーティクルテストカメラ処理[TestParticleCamera.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TestParticleCamera.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
TestParticleCamera::TestParticleCamera()
{	
	//パラメータ設定
	const float CameraAngleXZ = D3DXToRadian(45.0f);
	const float CameraAngleY = D3DXToRadian(60.0f);
	const float CameraLength = 50.0f;

	const D3DXVECTOR3 InitPos = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	transform.SetPosition(InitPos);
	transform.LookAt(Vector3::Zero);
}

/**************************************
更新処理
***************************************/
void TestParticleCamera::Update()
{
	static float angleXZ = 45.0f;
	static float angleY = 60.0f;

	Debug::Begin("Test Camera");
	Debug::Slider("AngleXZ", angleXZ, 0.0f, 360.0f);
	Debug::Slider("AngleY", angleY, -90.0f, 90.0f);
	Debug::End();

	D3DXVECTOR3 pos = D3DXVECTOR3(
		cosf(D3DXToRadian(angleY)) * cosf(D3DXToRadian(angleXZ)),
		sinf(D3DXToRadian(angleY)),
		cosf(D3DXToRadian(angleY)) * -sinf(D3DXToRadian(angleXZ)))  * 50.0f;

	transform.SetPosition(pos);

	Camera::Update();
}
