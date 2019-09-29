//=====================================
//
//クロスフィルタコントローラヘッダ[CrossFilterController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CROSSFILTERCONTROLLER_H_
#define _CROSSFILTERCONTROLLER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"
#include "BaseEffectController.h"
#include "Effect/BloomFilter.h"
#include "Effect/CrossBlurFilter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class CrossFilterController : public BaseSingleton<CrossFilterController>, public BaseEffectController
{
public:
	friend class BaseSingleton<CrossFilterController>;

	void Update();
	void Draw(LPDIRECT3DTEXTURE9 targetTexture = NULL);

private:
	CrossFilterController();
	~CrossFilterController();

	void SampleBrightness(LPDIRECT3DTEXTURE9 targetTexture);
	void ProcessBlur();
	void Blend();

	BloomFilter *bloomFilter;
	CrossBlurFilter *blurFilter;

	LPDIRECT3DTEXTURE9 blurTexture[3][2];
	LPDIRECT3DSURFACE9 blurSurface[3][2];

	LPDIRECT3DTEXTURE9 sampleTexture;
	LPDIRECT3DSURFACE9 sampleSurface;

	D3DVIEWPORT9 blurViewPort[3];
	D3DVIEWPORT9 oldViewPort;

	int cntBlur;
};

#endif