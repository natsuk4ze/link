//=====================================
//
//アニメコンテナ処理[AnimContainer.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "AnimContainer.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
フレームの描画処理
***************************************/
void AnimContainer::DrawFrame(LPD3DXFRAME frame)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPD3DXMESHCONTAINER meshContainer;

	if (frame == NULL)
	{
		return;
	}

	meshContainer = frame->pMeshContainer;
	while (meshContainer != NULL)
	{
		DrawMeshContainer(meshContainer, frame);
		meshContainer = meshContainer->pNextMeshContainer;
	}

	DrawFrame(frame->pFrameSibling);
	DrawFrame(frame->pFrameFirstChild);
}

/**************************************
メッシュコンテナの描画処理
***************************************/
void AnimContainer::DrawMeshContainer(LPD3DXMESHCONTAINER meshContainerBase, LPD3DXFRAME frameBase)
{
	D3DXMESHCONTAINER_DERIVED* meshContainer = (D3DXMESHCONTAINER_DERIVED*)meshContainerBase;
	D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)frameBase;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UINT iMaterial;
	UINT numBlend;
	UINT iAttrb;
	DWORD attrbIdPrev;
	LPD3DXBONECOMBINATION boneComb;

	UINT iMatrixIndex;
	D3DXMATRIXA16 mtxTemp;
	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);

	//スキンメッシュの場合の描画
	if (meshContainer->pSkinInfo != NULL)
	{
		attrbIdPrev = UNUSED32;
		boneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(meshContainer->boneCombinationBuf->GetBufferPointer());

		for (iAttrb = 0; iAttrb < meshContainer->boneNum; iAttrb++)
		{
			numBlend = 0;
			for (DWORD i = 0; i < meshContainer->boneWeightNum; i++)
			{
				if (boneComb[iAttrb].BoneId[i] != UINT_MAX)
				{
					numBlend = i;
				}
			}

			if (caps.MaxVertexBlendMatrices >= numBlend + 1)
			{
				for (DWORD i = 0; i < meshContainer->boneWeightNum; i++)
				{
					iMatrixIndex = boneComb[iAttrb].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(&mtxTemp, &meshContainer->boneOffsetMatrices[iMatrixIndex],
							meshContainer->boneMatrices[iMatrixIndex]);
						pDevice->SetTransform(D3DTS_WORLDMATRIX(i), &mtxTemp);
					}
				}

				pDevice->SetRenderState(D3DRS_VERTEXBLEND, numBlend);

				if ((attrbIdPrev != boneComb[iAttrb].AttribId) || (attrbIdPrev == UNUSED32))
				{
					pDevice->SetMaterial(&meshContainer->pMaterials[boneComb[iAttrb].AttribId].MatD3D);
					pDevice->SetTexture(0, meshContainer->textures[boneComb[iAttrb].AttribId]);
					attrbIdPrev = boneComb[iAttrb].AttribId;
				}

				meshContainer->MeshData.pMesh->DrawSubset(iAttrb);
			}
		}
		pDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);
	}
	//通常メッシュの描画
	else
	{
		pDevice->SetTransform(D3DTS_WORLD, &frame->combiendTransformMatrix);
		for (iMaterial = 0; iMaterial < meshContainer->NumMaterials; iMaterial++)
		{
			pDevice->SetMaterial(&meshContainer->pMaterials[iMaterial].MatD3D);
			pDevice->SetTexture(0, meshContainer->textures[iMaterial]);
			meshContainer->MeshData.pMesh->DrawSubset(iMaterial);
		}
	}
}

/**************************************
フレーム行列の更新
***************************************/
void AnimContainer::UpdateFrameMatrixes(LPD3DXFRAME frameBase, LPD3DXMATRIX parentMatrix)
{
	D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)frameBase;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (frameBase == NULL || parentMatrix == NULL)
	{
		return;
	}

	D3DXMatrixMultiply(&frame->combiendTransformMatrix, &frame->TransformationMatrix, parentMatrix);

	UpdateFrameMatrixes(frame->pFrameSibling, parentMatrix);
	UpdateFrameMatrixes(frame->pFrameFirstChild, &frame->combiendTransformMatrix);
}

/**************************************
特定のボーン行列の取得
***************************************/
D3DXMATRIX AnimContainer::GetBoneMatrix(const char* boneName)
{
	char message[64];
	D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)SearchBoneFrame(boneName, rootFrame);

	//見つかった場合
	if (frame != NULL && frame->Name != NULL && strcmp(frame->Name, boneName) == 0)
	{
		return frame->combiendTransformMatrix;
	}
	//見つからなかった場合
	else
	{
		sprintf_s(message, "Find %s Bone Failed!", boneName);
		MessageBox(0, message, "Error", 0);
		D3DXMATRIX tmpMatrix;
		D3DXMatrixIdentity(&tmpMatrix);
		return tmpMatrix;
	}
}

/**************************************
特定のボーンを探す
***************************************/
D3DXFRAME_DERIVED* AnimContainer::SearchBoneFrame(const char* boneName, D3DXFRAME* frame)
{
	D3DXFRAME_DERIVED* p = NULL;

	if (frame == NULL)
	{
		return NULL;
	}

	if (frame->Name != NULL && strcmp(frame->Name, boneName) == 0)
	{
		p = (D3DXFRAME_DERIVED*)frame;
		return p;
	}

	if (frame->pFrameSibling != NULL)
	{
		p = SearchBoneFrame(boneName, frame->pFrameSibling);
		if (p != NULL && strcmp(p->Name, boneName) == 0)
		{
			return p;
		}
	}

	if (frame->pFrameFirstChild != NULL)
	{
		p = SearchBoneFrame(boneName, frame->pFrameFirstChild);
		if (p != NULL && strcmp(p->Name, boneName) != 0)
		{
			return p;
		}
	}

	return NULL;

}

/**************************************
アニメーション読み込み処理
***************************************/
HRESULT AnimContainer::LoadAnimation(LPCSTR setName, int setNo)
{
	char message[64];

	if (FAILED(animController->GetAnimationSetByName(setName, &status[setNo].animSet)))
	{
		sprintf_s(message, "Can't find %s Animationset !", setName);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	status[setNo].setname = status[setNo].animSet->GetName();

	return S_OK;
}

/**************************************
終了処理
***************************************/
AnimContainer::~AnimContainer()
{
	SAFE_DELETE(status);
	SAFE_RELEASE(animController);
}

/**************************************
更新処理
***************************************/
void AnimContainer::Update(float time)
{
	AnimCallBackHandler callBackHandler;
	callBackHandler.animContainer = this;
	callBackHandler.setName = status[currentAnimID].setname;

	//合成中か否かを判定
	status[currentAnimID].currentWeightTime += time;

	if (status[currentAnimID].currentWeightTime <= status[currentAnimID].shiftTime)
	{
		//合成中。ウェイトを算出
		float weight = status[currentAnimID].currentWeightTime / status[currentAnimID].shiftTime;

		//ウェイトを登録
		animController->SetTrackWeight(0, weight);		//現在のアニメーション
		animController->SetTrackWeight(1, 1 - weight);	//前のアニメーション
	}
	else
	{
		//合成終了中
		animController->SetTrackWeight(0, 1.0f);			//現在のアニメーション
		animController->SetTrackWeight(1, false);		//前のアニメーションを無効にする
	}

	//時間を更新
	animController->AdvanceTime(time, &callBackHandler);

	return;
}

/**************************************
描画処理
***************************************/
void AnimContainer::Draw(LPD3DXMATRIX worldMtx)
{
	UpdateFrameMatrixes(rootFrame, worldMtx);
	DrawFrame(rootFrame);
}

/**************************************
アニメーションの切り替え処理
***************************************/
void AnimContainer::ChangeAnim(UINT animID, float playSpeed, bool forceChange)
{
	D3DXTRACK_DESC TD;		//トラックの能力

	isMotionEnd = false;
	isStopMove = false;
	keyFrameCount = 0;

	//指定のアニメーションIDの存在をチェック
	if (animID > (UINT)animSetNum)
	{
		MessageBox(0, "AnimationsSet Don't Exist", "Error", 0);
		return;
	}

	//異なるアニメーションであるかをチェック
	//更新する必要がない
	if (currentAnimID == animID && !forceChange)
	{
		return;
	}

	//現在のアニメーションセットの設定値を取得
	animController->GetTrackDesc(0, &TD);

	//今のアニメーションをトラック１に移行し、トラックの設定も移行
	animController->SetTrackAnimationSet(1, status[currentAnimID].animSet);
	animController->SetTrackDesc(1, &TD);
	animController->SetTrackSpeed(1, 0.0f);

	//新しいアニメーションをトラック０に設定
	animController->SetTrackAnimationSet(0, status[animID].animSet);

	//トラック０のスピード設定
	animController->SetTrackSpeed(0, playSpeed);

	//トラック０の位置は最初からに設定
	animController->SetTrackPosition(0, 0.0f);

	//トラックの合成を許可
	animController->SetTrackEnable(0, true);
	animController->SetTrackEnable(1, true);

	//ウェイト時間を初期化
	status[animID].currentWeightTime = 0.0f;
	animController->ResetTime();

	//現在のアニメーション番号を切り替え
	prevAnimID = currentAnimID;
	currentAnimID = animID;

	return;
}

/**************************************
動作開始にかかる時間を設定
***************************************/
void AnimContainer::SetShiftTime(UINT animID, float interval)
{
	//指定のアニメーションIDの存在をチェック
	if (animID > (UINT)animSetNum)
	{
		MessageBox(0, "AnimationSet Don't Exist", "Error", 0);
		return;
	}

	//シフト時間を登録
	status[animID].shiftTime = interval;

	return;
}

/**************************************
オブジェクトを作るう
***************************************/
AnimContainer::AnimContainer(void)
{

}

/**************************************
アニメ再生の中断イベント
***************************************/
HRESULT AnimCallBackHandler::HandleCallback(UINT track, LPVOID callBackData)
{
	if (animContainer->keyFrameCount == 0)
	{
		animContainer->isStopMove = true;
	}
	else if (animContainer->keyFrameCount == 1)
	{
		animContainer->isMotionEnd = true;
		return D3D_OK;
	}

	animContainer->keyFrameCount++;

	return D3D_OK;
}

/**************************************
アニメーション中断イベントのKeyFramesを設置する
***************************************/
HRESULT AnimContainer::SetupCallbackKeyFrames(LPCSTR setName)
{
	//KeyFramesを設置する予定のAnimationSet
	ID3DXKeyframedAnimationSet* animSetTemp = 0;

	//KeyFrameを設置した新しいAnimationSet
	ID3DXCompressedAnimationSet *compressedAnimSet = 0;

	//エラーメッセージ
	char message[64];

	//設置するCallback Keysの数
	const UINT callbackNum = 2;
	D3DXKEY_CALLBACK keys[callbackNum];

	if (FAILED(animController->GetAnimationSetByName(setName, (ID3DXAnimationSet**)&animSetTemp)))
	{
		sprintf_s(message, "Setup Callback in %s AnimationSet Failed!", setName);
		MessageBox(0, message, "Error", 0);
		return E_FAIL;
	}

	//圧縮情報を作成
	ID3DXBuffer* compressedInfo = 0;
	animSetTemp->Compress(D3DXCOMPRESS_DEFAULT, 0.5f, 0, &compressedInfo);

	double ticks = animSetTemp->GetSourceTicksPerSecond();

	keys[0].Time = (float)(animSetTemp->GetPeriod() * (90.0f / 125.0f) * ticks);

	keys[1].Time = (float)(animSetTemp->GetPeriod() * 0.9f * ticks);

	D3DXCreateCompressedAnimationSet(animSetTemp->GetName(),
		animSetTemp->GetSourceTicksPerSecond(),
		animSetTemp->GetPlaybackType(), compressedInfo, callbackNum, keys, &compressedAnimSet);

	compressedInfo->Release();

	//圧縮前のデータを削除
	animController->UnregisterAnimationSet(animSetTemp);
	animSetTemp->Release();

	//圧縮したデータを設定
	animController->RegisterAnimationSet(compressedAnimSet);
	compressedAnimSet->Release();

	return S_OK;
}

/**************************************
アニメーションセット数取得処理
***************************************/
UINT AnimContainer::GetNumAnimationSets()
{
	return (UINT)animSetNum;
}

/**************************************
アニメーション中断イベントのKeyFramesを設置する
***************************************/
float AnimContainer::GetPeriodAnimation()
{
	return (float)status[currentAnimID].animSet->GetPeriod();
}