//=============================================================================
//
// 隕石イベントクラス [Meteorite.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "Meteorite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 隕石の半径
const float MeteoriteRadius = 3.0f;	
const float MeteoriteDistance = 200.0f;
const float FallSpeed = 4.0f;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 Meteorite::Device = nullptr;
LPD3DXMESH Meteorite::SphereMesh = nullptr;
D3DMATERIAL9 Meteorite::Material =
{
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// Diffuse color RGBA
	D3DXCOLOR(1.0f, 0.65f, 0.0f, 0.0f),	// Ambient color RGB
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Specular 'shininess'
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Emissive color RGB
	0.0f,								// Sharpness if specular highlight 
};

//=============================================================================
// コンストラクタ
//=============================================================================
Meteorite::Meteorite(D3DXVECTOR3 GoalPos) : GoalPos(GoalPos)
{
	Pos = GoalPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	FallDirection = GoalPos - Pos;
	D3DXVec3Normalize(&FallDirection, &FallDirection);

	// デバイス取得
	if (Device == nullptr)
	{
		Device = GetDevice();
	}

	// 球体メッシュを作成する
	if (SphereMesh == nullptr)
	{
		D3DXCreateSphere(Device, MeteoriteRadius, 16, 16, &SphereMesh, NULL);
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
Meteorite::~Meteorite()
{

}

//=============================================================================
// 更新
//=============================================================================
void Meteorite::Update()
{
	float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(GoalPos - Pos));

	if (Distance > pow(3.0f, 2))
	{
		Pos += FallDirection * FallSpeed;
	}
	else
	{
		this->UseFlag = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void Meteorite::Draw()
{
	D3DXMATRIX WorldMatrix, TransMatrix;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&WorldMatrix);

	// 移動を反映
	D3DXMatrixTranslation(&TransMatrix, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

	// ワールドマトリックスの設定
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// マテリアルの設定
	Device->SetMaterial(&Material);

	// 球体描画
	SphereMesh->DrawSubset(0);
}

