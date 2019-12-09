//=====================================
//
//SpaceGridEffect.h
//機能:スペースグリッドの描画エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SPACEGRIDEFFECT_H_
#define _SPACEGRIDEFFECT_H_

#include "../../main.h"
#include "../../Framework/Effect/SpriteEffect.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SpaceGridEffect : public SpriteEffect
{
public:
	SpaceGridEffect();
	~SpaceGridEffect();

	void SetAlpha(float alpha);

	void SetTime(float t);

private:
	LPDIRECT3DTEXTURE9 lumineMap;

	D3DXHANDLE hLumineTex;
	D3DXHANDLE hTime;
};
#endif