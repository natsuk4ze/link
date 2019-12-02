//=====================================
//
//AnimationResource.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AnimationResource.h"
#include "../Animation/MyAllocateHierarchy.h"
#include "../Animation/AnimContainer.h"

/**************************************
コンストラクタ
***************************************/
AnimationResource::AnimationResource() :
	rootFrame(NULL),
	animController(NULL),
	animSetNum(0)
{

}

/**************************************
デストラクタ
***************************************/
AnimationResource::~AnimationResource()
{
	//NOTE:エラーを治す
	return;
	MyAllocateHierarchy allocater = MyAllocateHierarchy();
	D3DXFrameDestroy(rootFrame, &allocater);

	SAFE_RELEASE(animController);
}

/**************************************
Xファイル読み込み
***************************************/
HRESULT AnimationResource::Load(const char * fileName, const char * errorSrc)
{
	char message[64];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MyAllocateHierarchy allocater = MyAllocateHierarchy();

	if (FAILED(D3DXLoadMeshHierarchyFromX(fileName,
		D3DXMESH_MANAGED,
		pDevice,
		&allocater,
		NULL,
		&rootFrame,
		&animController)))
	{
		sprintf_s(message, "Load %s Model Failed", errorSrc);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	if (FAILED(SetupBoneMatrixPointers(rootFrame, rootFrame)))
	{
		return E_FAIL;
	}

	animSetNum = animController->GetNumAnimationSets();

	return S_OK;
}

/**************************************
クローン処理
***************************************/
void AnimationResource::Clone(AnimContainer * container)
{
	animController->CloneAnimationController(
		animController->GetMaxNumAnimationOutputs(),
		animController->GetMaxNumAnimationSets(),
		animController->GetMaxNumTracks(),
		animController->GetMaxNumEvents(),
		&container->animController
	);

	container->rootFrame = rootFrame;
	container->animSetNum = animSetNum;

	container->status = new AnimStatus[animSetNum];
}

/**************************************
ボーン行列セットアップ
***************************************/
HRESULT AnimationResource::SetupBoneMatrixPointers(LPD3DXFRAME frameBase, LPD3DXFRAME frameRoot)
{
	if (frameBase->pMeshContainer != NULL)
	{
		D3DXFRAME_DERIVED* frame = NULL;
		D3DXMESHCONTAINER_DERIVED* meshContainer = (D3DXMESHCONTAINER_DERIVED*)frameBase->pMeshContainer;

		//スキンメッシュを持っていたらボーン行列を準備する
		if (meshContainer->pSkinInfo != NULL)
		{
			UINT cBones = meshContainer->pSkinInfo->GetNumBones();
			meshContainer->boneMatrices = new D3DXMATRIX*[cBones];
			for (UINT iBone = 0; iBone < cBones; iBone++)
			{
				frame = (D3DXFRAME_DERIVED*)D3DXFrameFind(frameRoot, meshContainer->pSkinInfo->GetBoneName(iBone));
				if (frame == NULL)
					return E_FAIL;

				meshContainer->boneMatrices[iBone] = &frame->combiendTransformMatrix;
			}
		}
	}

	//兄弟フレームのボーンをセットアップ
	if (frameBase->pFrameSibling != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(frameBase->pFrameSibling, frameRoot)))
			return E_FAIL;
	}

	//子フレームのボーンをセットアップ
	if (frameBase->pFrameFirstChild != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(frameBase->pFrameFirstChild, frameRoot)))
			return E_FAIL;
	}


	return S_OK;
}
