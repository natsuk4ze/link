//=====================================
//
//Viewer3D.cpp
//機能:2Dオブジェクトの3D表示
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Viewer3D.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
Viewer3D::Viewer3D(DWORD sizeX, DWORD sizeY, const D3DXVECTOR2& worldSize) :
	transform(new Transform())
{
	//レンダーターゲット作成
	MakeRenderTarget(sizeX, sizeY);

	//頂点バッファ作成
	MakeVertexBuffer(worldSize);
}

/**************************************
デストラクタ
***************************************/
Viewer3D::~Viewer3D()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTarget);

	SAFE_DELETE(transform);
}

/**************************************
2D描画開始処理
***************************************/
void Viewer3D::Begin2D()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット切り替え
	pDevice->GetRenderTarget(0, &defaultSurface);
	pDevice->SetRenderTarget(0, renderSurface);

	//レンダーターゲットクリア
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);
}

/**************************************
2D描画終了処理
***************************************/
void Viewer3D::End2D()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲットを元に戻す
	pDevice->SetRenderTarget(0, defaultSurface);

	//参照を解放
	SAFE_RELEASE(defaultSurface);
}

/**************************************
3D描画処理
***************************************/
void Viewer3D::Draw3D()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//現在のレンダーステートを保存
	DWORD flgLighting, flgEnableZ, flgWriteenableZ;
	pDevice->GetRenderState(D3DRS_LIGHTING, &flgLighting);
	pDevice->GetRenderState(D3DRS_ZENABLE, &flgEnableZ);
	pDevice->GetRenderState(D3DRS_ZWRITEENABLE, &flgWriteenableZ);

	//レンダーステート切り替え
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//FVF保存＆切り替え
	DWORD fvf;
	pDevice->GetFVF(&fvf);
	pDevice->SetFVF(FVF_VERTEX_3D);

	//頂点バッファをセット
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	//UIを描画したテクスチャをセット
	pDevice->SetTexture(0, renderTarget);

	//ワールド行列を計算しセット
	D3DXMATRIX mtxWorld;
	mtxWorld = transform->GetMatrix();
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//レンダーステートを元に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, flgLighting);
	pDevice->SetRenderState(D3DRS_ZENABLE, flgEnableZ);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, flgWriteenableZ);

	//FVFを元に戻す
	pDevice->SetFVF(FVF_VERTEX_2D);
}

/**************************************
座標設定処理
***************************************/
void Viewer3D::SetPosition(const D3DXVECTOR3 & position)
{
	transform->SetPosition(position);
}

/**************************************
回転設定処理
***************************************/
void Viewer3D::SetRotation(float x, float y, float z)
{
	transform->SetRotation(Vector3::Zero);
	transform->Rotate(x, y, z);
}

/**************************************
頂点バッファ作成処理
***************************************/
void Viewer3D::MakeVertexBuffer(const D3DXVECTOR2& size)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(size.x, size.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(size.x, -size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
レンダーターゲット作成処理
***************************************/
void Viewer3D::MakeRenderTarget(DWORD sizeX, DWORD sizeY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲットとなるテクスチャを作成
	pDevice->CreateTexture(
		sizeX,		//テクスチャの横幅
		sizeY,		//テクスチャの縦幅
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTarget,				//結果を格納するインターフェース
		0);

	//作成したテクスチャからサーフェイスを取得
	renderTarget->GetSurfaceLevel(0, &renderSurface);
}