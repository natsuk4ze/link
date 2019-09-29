//=====================================
//
//メッシュヒエラルキーヘッダ[MyAllocateHierarchy.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MYALLOCATEHIERARCHY_H_
#define _MYALLOCATEHIERARCHY_H_

#include "../../main.h"
#undef new
/**************************************
マクロ定義
***************************************/

/**************************************
D3DXFRAME派生構造体
***************************************/
struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 combiendTransformMatrix;

	void* operator new(size_t i)
	{
		return _aligned_malloc(i, 16);
	}
};

/**************************************
D3DXMESHCONTAINER派生構造体
***************************************/
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9 *textures;

	//スキンメッシュ情報
	LPD3DXMESH originMesh;				//オリジナルメッシュ
	DWORD boneNum;						//ボーン数
	DWORD boneWeightNum;				//1つの頂点に影響を及ぼす重みの数
	LPD3DXBUFFER boneCombinationBuf;	//ボーン情報のバッファ
	D3DXMATRIX** boneMatrices;			//全ボーンの行列のポインタ配列
	D3DXMATRIX* boneOffsetMatrices;		//ボーンのオフセット行列
	DWORD numPaletteEntries;			//パレットサイズ
};

/**************************************
ID3DXAllocateHierarchy派生クラス
***************************************/
class MyAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	MyAllocateHierarchy(void) {}
	virtual ~MyAllocateHierarchy(void) {}

	/***********************************
	フレームオブジェクト作成処理
	************************************/
	STDMETHOD(CreateFrame)(THIS_
		LPCSTR name,
		LPD3DXFRAME *ppNewFrame);

	/***********************************
	メッシュコンテナ作成処理
	************************************/
	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstance,
		DWORD numMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	/***********************************
	フレームオブジェクト解放処理
	************************************/
	STDMETHOD(DestroyFrame)(THIS_
		LPD3DXFRAME pFrameToFree);

	/***********************************
	メッシュコンテナ解放処理
	************************************/
	STDMETHOD(DestroyMeshContainer)(THIS_
		LPD3DXMESHCONTAINER pMeshContainerToFree);

protected:
	//文字列コピー
	LPSTR CopyStr(LPCSTR name);

	HRESULT AllocateName(LPCSTR name, LPSTR* newName);
	HRESULT GenerateSkinnedMesh(LPDIRECT3DDEVICE9 pDevice, D3DXMESHCONTAINER_DERIVED *meshContainer);
};

#endif