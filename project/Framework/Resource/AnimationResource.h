//=====================================
//
//AnimationResource.h
//機能:アニメーションResources
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ANIMATIONRESOURCE_H_
#define _ANIMATIONRESOURCE_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class AnimContainer;

/**************************************
クラス定義
***************************************/
class AnimationResource
{
public:
	AnimationResource();
	virtual ~AnimationResource();

	HRESULT Load(const char* fileName, const char* errorSrc);

	void Clone(AnimContainer* container);

private:
	LPD3DXFRAME rootFrame;
	LPD3DXANIMATIONCONTROLLER animController;

	int animSetNum;

	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME frameBase, LPD3DXFRAME frameRoot);
};
#endif