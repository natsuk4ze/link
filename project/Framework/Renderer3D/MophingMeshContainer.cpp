//=====================================
//
//MorphingMeshContainer.cpp
//機能:モーフィングメッシュコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MophingMeshContainer.h"
#include "../Effect/MophingEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
MorphingMeshContainer::MorphingMeshContainer() :
	indexBuff(NULL),
	declare(NULL),
	effect(NULL),
	currentIndex(-1), nextIndex(-1), t(0.0f)
{
	effect = new MophingEffect();
}

/**************************************
デストラクタ
***************************************/
MorphingMeshContainer::~MorphingMeshContainer()
{
	for (auto&& mesh : meshTable)
	{
		SAFE_RELEASE(mesh);
	}

	for (auto&& container : textureContainer)
	{
		for (auto&& tex : container)
		{
			SAFE_RELEASE(tex);
		}
	}

	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(declare);

	SAFE_DELETE(effect);

	materialContainer.clear();
	attributeTable.clear();
}

/**************************************
メッシュ登録処理
***************************************/
void MorphingMeshContainer::RegisterVertex(unsigned index)
{
	if (mesh == NULL)
		return;

	if (meshTable.size() < index + 1)
	{
		meshTable.resize(index + 1, NULL);
		textureContainer.resize(index + 1);
		materialContainer.resize(index + 1);
	}

	//バッファ登録
	meshTable[index] = mesh;
	meshTable[index]->AddRef();
	fvf = mesh->GetFVF();

	if (indexBuff == NULL)
		mesh->GetIndexBuffer(&indexBuff);

	//マテリアル登録
	materialContainer[index].reserve(materialNum);
	for (unsigned i = 0; i < materialNum; i++)
	{
		materialContainer[index].push_back(materials[i]);
	}

	//テクスチャ登録
	textureContainer[index].resize(materialNum);
	for(unsigned i = 0; i < materialNum; i++)
	{
		textureContainer[index][i] = textures[i];
		textures[i]->AddRef();
	}


	//属性テーブル取得
	if (attributeTable.empty())
	{
		attributeTable.resize(materialNum);
		mesh->GetAttributeTable(&attributeTable[0], NULL);
	}

	//頂点宣言作成
	if (declare == NULL)
	{
		D3DVERTEXELEMENT9 elem[65];
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		ZeroMemory(elem, sizeof(D3DVERTEXELEMENT9) * 65);
		mesh->GetDeclaration(elem);

		for (int i = 0; i < 65; i++)
		{
			if (elem[i].Type != D3DDECLTYPE_UNUSED)
				continue;

			for (int j = i; j < i * 2; j++)
			{
				elem[j] = elem[j - i];
				elem[j].Stream = 1;
				elem[j].UsageIndex = 1;
			}
			elem[i * 2] = D3DDECL_END();
			break;
		}

		HRESULT res = pDevice->CreateVertexDeclaration(elem, &declare);
		assert(res == S_OK);
	}

	//インデックス設定
	if (currentIndex < 0)
	{
		nextIndex = currentIndex = index;
	}
}

/**************************************
描画処理
***************************************/
void MorphingMeshContainer::Draw(const D3DXMATRIX & mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//メッシュから頂点バッファを取得
	LPDIRECT3DVERTEXBUFFER9 vtx0, vtx1;
	meshTable[currentIndex]->GetVertexBuffer(&vtx0);
	meshTable[nextIndex]->GetVertexBuffer(&vtx1);

	//ストリームソース設定
	pDevice->SetStreamSource(0, vtx0, 0, D3DXGetFVFVertexSize(fvf));
	pDevice->SetStreamSource(1, vtx1, 0, D3DXGetFVFVertexSize(fvf));

	//インデックスバッファ設定
	pDevice->SetIndices(indexBuff);

	//頂点宣言設定
	pDevice->SetVertexDeclaration(declare);

	//シェーダへパラメータを設定
	effect->SetWorld(mtxWorld);
	effect->SetTime(t);

	//描画
	for (unsigned i = 0; i < materialNum; i++)
	{
		effect->SetMaterial(materialContainer[currentIndex][i]);
		effect->SetNextMaterial(materialContainer[nextIndex][i]);

		pDevice->SetTexture(0, textureContainer[currentIndex][i]);
		effect->SetNextTexture(textureContainer[nextIndex][i]);

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
}

/**************************************
現在のメッシュ選択処理
***************************************/
void MorphingMeshContainer::SetCurrent(unsigned index)
{
	if (index < 0 || index >= meshTable.size())
		return;

	currentIndex = index;
}

/**************************************
次のメッシュ選択処理
***************************************/
void MorphingMeshContainer::SetNext(unsigned next)
{
	if (next < 0 || next >= meshTable.size())
		return;

	nextIndex = next;
}

/**************************************
変化量設定処理
***************************************/
void MorphingMeshContainer::SetChange(float t)
{
	this->t = t;
}

/**************************************
Draw()を禁止するためにprivate化
***************************************/
void MorphingMeshContainer::Draw() {}

/**************************************
Draw()を禁止するためにprivate化
***************************************/
void MorphingMeshContainer::Draw(RendererEffect & effect) {}
