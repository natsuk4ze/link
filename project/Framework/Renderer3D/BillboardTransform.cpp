//=====================================
//
//ビルボードトランスフォーム処理[BillboardTransform.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BillboardTransform.h"
#include "../Camera/Camera.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
void BillboardTransform::SetWorld(const D3DXMATRIX * parent) const
{
	D3DXMATRIX world, rotation, view, invView;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//回転
	D3DXMatrixRotationQuaternion(&world, &this->rotation);

	//ビルボード処理
	pDevice->GetTransform(D3DTS_VIEW, &view);
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixMultiply(&world, &world, &invView);

	//スケール
	world._11 *= scale.x;
	world._12 *= scale.x;
	world._13 *= scale.x;

	world._21 *= scale.y;
	world._22 *= scale.y;
	world._23 *= scale.y;

	world._31 *= scale.z;
	world._32 *= scale.z;
	world._33 *= scale.z;

	//移動
	world._41 = position.x;
	world._42 = position.y;
	world._43 = position.z;

	//親を反映
	if (parent != NULL)
	{
		D3DXMatrixMultiply(&world, parent, &world);
	}

	pDevice->SetTransform(D3DTS_WORLD, &world);
}

/**************************************
グローバル変数
***************************************/
D3DXMATRIX BillboardTransform::GetMatrix() const
{
	/*************************************
	NOTE:正直に行列計算するより、要素を直接計算した方が早かったので
	回転だけ行列で、それ以外は直接計算している
	*************************************/
	D3DXMATRIX world;

	//回転
	D3DXMatrixRotationQuaternion(&world, &this->rotation);

	////ビルボード処理
	D3DXMATRIX invView = Camera::GetInverseViewMtx();
	invView._41 = invView._42 = invView._43 = 0.0f;
	D3DXMatrixMultiply(&world, &world, &invView);

	//スケール
	world._11 *= scale.x;
	world._12 *= scale.x;
	world._13 *= scale.x;

	world._21 *= scale.y;
	world._22 *= scale.y;
	world._23 *= scale.y;

	world._31 *= scale.z;
	world._32 *= scale.z;
	world._33 *= scale.z;

	//移動
	world._41 = position.x;
	world._42 = position.y;
	world._43 = position.z;

	return world;
}
