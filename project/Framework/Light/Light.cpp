//=====================================
//
//Light.cpp
//機能:ライト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Light.h"

namespace Light
{
	/**************************************
	グローバル変数
	***************************************/
	static D3DLIGHT9 light[NUM_LIGHT];
	static int NumLigt = 3;

	/**************************************
	初期化処理
	***************************************/
	void Init()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXVECTOR3 vecDir;
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&light[0], sizeof(D3DLIGHT9));
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&light[2], sizeof(D3DLIGHT9));
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&light[1], sizeof(D3DLIGHT9));

		// ライト0の設定
		light[0].Type = D3DLIGHT_DIRECTIONAL;
		light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light[0].Ambient = D3DXCOLOR(0.1f, 0.1f, 0.5f, 1.0f);
		vecDir = D3DXVECTOR3(0.80f, -1.0f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[0].Direction, &vecDir);

		// ライト1の設定
		light[1].Type = D3DLIGHT_DIRECTIONAL;
		light[1].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		light[1].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		vecDir = D3DXVECTOR3(-0.0f, 1.00f, -0.50f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[1].Direction, &vecDir);

		// ライト2の設定
		light[2].Type = D3DLIGHT_DIRECTIONAL;
		light[2].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		light[2].Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		vecDir = D3DXVECTOR3(-0.40f, -0.5f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[2].Direction, &vecDir);

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(0, &light[0]);
		pDevice->LightEnable(0, TRUE);

		//// ライトをレンダリングパイプラインに設定
		//pDevice->SetLight(1, &light[1]);
		//pDevice->LightEnable(1, TRUE);

		//// ライトをレンダリングパイプラインに設定
		//pDevice->SetLight(2, &light[2]);
		//pDevice->LightEnable(2, TRUE);

		// ライティングモード
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	/**************************************
	ライト情報取得処理
	***************************************/
	D3DLIGHT9 GetData(int id)
	{
		if (id >= NUM_LIGHT)
			return D3DLIGHT9();
		else
			return light[id];
	}

	/**************************************	
	ライト数取得処理
	***************************************/
	int LightMax()
	{
		return NumLigt;
	}

}
