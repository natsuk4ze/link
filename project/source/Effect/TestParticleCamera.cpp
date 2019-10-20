//=====================================
//
//パーティクルテストカメラ処理[TestParticleCamera.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TestParticleCamera.h"

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
}
