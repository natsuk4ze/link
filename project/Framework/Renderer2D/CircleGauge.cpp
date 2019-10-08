//=====================================
//
//CircleGauge.cpp
//機能:円形ゲージ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "CircleGauge.h"
#include "../Resource/ResourceManager.h"
#include "../Tool/DebugWindow.h"

/**************************************
コンストラクタ
***************************************/
CircleGauge::CircleGauge(const D3DXVECTOR2 & Size) :
	vtxBuff(NULL),
	texture(NULL),
	transform(NULL),
	effect(NULL),
	percent(0.0f),
	start(FillStart::Top)
{
	transform = new Transform();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファ作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	//エフェクト読み込み
	HRESULT res = D3DXCreateEffectFromFile(pDevice, "data/EFFECT/CircleGauge.cfx", 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);
	if (res != S_OK)
	{
		D3DXCreateEffectFromFile(pDevice, "Shaders/CircleGauge.fx", 0, 0, 0, 0, &effect, 0);
	}

	//ハンドル取得
	hPercent = effect->GetParameterByName(0, "percent");
	hMatrix = effect->GetParameterByName(0, "transform");
	hProj = effect->GetParameterByName(0, "projection");

	//頂点バッファ初期化
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-Size.x * 0.5f, -Size.y * 0.5f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( Size.x * 0.5f, -Size.y * 0.5f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-Size.x * 0.5f,  Size.y * 0.5f, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( Size.x * 0.5f,  Size.y * 0.5f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
デストラクタ
***************************************/
CircleGauge::~CircleGauge()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
	SAFE_RELEASE(effect);

	SAFE_DELETE(transform);
}

/**************************************
描画処理
***************************************/
void CircleGauge::Draw()
{
	Debug::Begin("Circle");
	Debug::Slider("per", percent, 0.0f, 1.0f);
	effect->SetFloat(hPercent, percent);
	Debug::End();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//描画前の下準備
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetTexture(0, texture);

	//頂点変換座標を設定
	D3DXMATRIX mtxTrans = transform->GetMatrix();
	effect->SetMatrix(hMatrix, &mtxTrans);

	//投影行列設定
	D3DXMATRIX proj;
	D3DXMatrixIdentity(&proj);
	proj._11 = 2.0f / SCREEN_WIDTH;
	proj._22 = - 2.0f / SCREEN_HEIGHT;
	proj._41 = -1;
	proj._42 = 1;
	effect->SetMatrix(hProj, &proj);
	effect->CommitChanges();

	//描画開始
	effect->Begin(0, 0);
	effect->BeginPass(start);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//描画終了
	effect->EndPass();
	effect->End();
}

/**************************************
テクスチャ読み込み処理
***************************************/
void CircleGauge::LoadTexture(const char * path)
{
	ResourceManager::Instance()->GetTexture(path, texture);
}

/**************************************
座標設定処理
***************************************/
void CircleGauge::SetPosition(const D3DXVECTOR3 & pos)
{
	transform->SetPosition(pos);
}

/**************************************
回転設定処理
***************************************/
void CircleGauge::SetRotation(const D3DXVECTOR3 & rot)
{
	transform->SetRotation(rot);
}

/**************************************
スケール設定処理
***************************************/
void CircleGauge::SetScale(const D3DXVECTOR3 & scale)
{
	transform->SetScale(scale);
}

/**************************************
パーセント設定処理
***************************************/
void CircleGauge::SetPercent(float per)
{
	percent = 1.0f - Math::Clamp(0.0f, 1.0f, per);
}

/**************************************
ゲージ始点設定処理
***************************************/
void CircleGauge::SetFillStart(FillStart start)
{
	this->start = start;
}
