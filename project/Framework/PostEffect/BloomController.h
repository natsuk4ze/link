//=====================================
//
//ブルームコントローラヘッダ[BloomController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLOOMCONTROLLER_H_
#define _BLOOMCONTROLLER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"
#include "BaseEffectController.h"
#include "Effect/BloomFilter.h"
#include "Effect/BlurFilter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BloomController : public BaseSingleton<BloomController>, public BaseEffectController
{
public:
	friend class BaseSingleton<BloomController>;

	void Update();
	void Draw(LPDIRECT3DTEXTURE9 targetTexture = NULL);

private:
	BloomController();
	~BloomController();

	void SampleBrightness(LPDIRECT3DTEXTURE9 targetTexture);
	void ProcessBlur();
	void BlendBloom();

	BloomFilter *bloomFilter;
	BlurFilter *blurFilter;

	LPDIRECT3DTEXTURE9 blurTexture[3][2];
	LPDIRECT3DSURFACE9 blurSurface[3][2];
	D3DVIEWPORT9 blurViewPort[3];
	D3DVIEWPORT9 oldViewPort;

	int cntBlur;

};

#endif