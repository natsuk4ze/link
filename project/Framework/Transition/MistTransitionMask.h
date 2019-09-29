//=====================================
//
//ミストトランジションマスクヘッダ[MistTransitionMask.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MISTTRANSITIONMASK_H_
#define _MISTTRANSITIONMASK_H_

#include "../../main.h"
#include "BaseTransitionMask.h"
#include "../Math/Easing.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class MistTransitionMask : public BaseTransitionMask
{
public:
	MistTransitionMask();
	~MistTransitionMask();

	MaskResult Update() override;
	void Draw() override;
	void Set(bool isOut) override;

private:
	DWORD alphaRef;
	int cntFrame;

	float startRef, endRef;
	EaseType type;

	Polygon2D *polygon;
};

#endif