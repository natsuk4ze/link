//=====================================
//
//インスタンシングメッシュコンテナ処理[InstancingMeshContainer.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "InstancingMeshContainer.h"
#include "../Effect/InstancingMeshEffect.h"

/**************************************
コンストラクタ
***************************************/
InstancingMeshContainer::InstancingMeshContainer(unsigned MaxNum) :
	MaxInstance(MaxNum),
	vtxBuff(nullptr),
	indexBuff(nullptr),
	declare(nullptr),
	transformBuffer(nullptr),
	effect(nullptr),
	pWorld(nullptr)
{
	effect = new InstancingMeshEffect();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//SRTバッファを作成
	pDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * MaxNum, 0, 0, D3DPOOL_MANAGED, &transformBuffer, 0);
}

/**************************************
デストラクタ
***************************************/
InstancingMeshContainer::~InstancingMeshContainer()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(declare);
	
	SAFE_DELETE(effect);
}

/**************************************
読み込み処理
***************************************/
void InstancingMeshContainer::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各バッファを取得
	mesh->GetVertexBuffer(&vtxBuff);
	mesh->GetIndexBuffer(&indexBuff);
	fvf = mesh->GetFVF();

	//属性テーブルを取得
	attributeTable.resize(materialNum);
	mesh->GetAttributeTable(&attributeTable[0], NULL);

	//頂点宣言を作成
	MakeDeclaration(mesh);
}

/**************************************
描画処理
***************************************/
void InstancingMeshContainer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点宣言と各バッファをセット
	pDevice->SetVertexDeclaration(declare);

	pDevice->SetStreamSource(0, vtxBuff, 0, D3DXGetFVFVertexSize(fvf));
	pDevice->SetStreamSource(1, transformBuffer, 0, sizeof(D3DXMATRIX));
	pDevice->SetIndices(indexBuff);

	//ストリームソース周波数設定
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | indexTransform);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//マテリアルごとに描画
	for (unsigned i = 0; i < materialNum; i++)
	{
		effect->SetMaterial(materials[i]);

		pDevice->SetTexture(0, textures[i]);

		effect->Begin();
		effect->BeginPass(0);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0,
			attributeTable[i].VertexStart,
			attributeTable[i].VertexCount,
			attributeTable[i].VertexStart * 3,
			attributeTable[i].FaceCount);

		effect->EndPass();
		effect->End();
	}

	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
}


/**************************************
SRTバッフファロック処理
***************************************/
void InstancingMeshContainer::Lock()
{
	assert(pWorld == nullptr);
	indexTransform = 0;
	transformBuffer->Lock(0, 0, (void**)&pWorld, 0);
}

/**************************************
SRTアンロック処理
***************************************/
void InstancingMeshContainer::Unlock()
{
	assert(pWorld != nullptr);
	transformBuffer->Unlock();
	pWorld = nullptr;
}

/**************************************
SRT情報埋め込み処理
***************************************/
bool InstancingMeshContainer::EmbedTranform(const Transform & transform)
{
	if (indexTransform >= MaxInstance)
		return false;

	*pWorld = transform.GetMatrix();
	
	pWorld++;
	indexTransform++;

	return true;
}

/**************************************
頂点宣言作成
***************************************/
void InstancingMeshContainer::MakeDeclaration(LPD3DXMESH mesh)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVERTEXELEMENT9 elem[65];
	ZeroMemory(&elem[0], sizeof(D3DVERTEXELEMENT9) * 65);
	mesh->GetDeclaration(elem);

	for (int i = 0; i < 65; i++)
	{
		if (elem[i].Type != D3DDECLTYPE_UNUSED)
			continue;

		elem[i] = D3DVERTEXELEMENT9{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 };
		elem[i + 1] = D3DVERTEXELEMENT9{ 1, sizeof(float) * 4, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 };
		elem[i + 2] = D3DVERTEXELEMENT9{ 1, sizeof(float) * 8, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 };
		elem[i + 3] = D3DVERTEXELEMENT9{ 1, sizeof(float) * 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 };
		elem[i + 4] = D3DDECL_END();
		break;
	}

	pDevice->CreateVertexDeclaration(elem, &declare);
}
