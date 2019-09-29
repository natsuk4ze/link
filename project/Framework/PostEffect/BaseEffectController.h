//=====================================
//
//ベースエフェクトコントローラヘッダ[BaseEffectController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEEFFECTCONTROLLER_H_
#define _BASEEFFECTCONTROLLER_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BaseEffectController
{
public:
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DTEXTURE9 targetTexture = NULL) = 0;

	virtual void SetDefaultTarget(LPDIRECT3DTEXTURE9 texture);

protected:
	LPDIRECT3DTEXTURE9 defaultTarget;
};

#endif