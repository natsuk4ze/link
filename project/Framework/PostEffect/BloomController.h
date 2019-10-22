//=====================================
//
//ブルームコントローラヘッダ[BloomController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLOOMCONTROLLER_H_
#define _BLOOMCONTROLLER_H_

#include "../../main.h"
#include "BaseEffectController.h"
#include "Effect/BloomFilter.h"
#include "Effect/BlurFilter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BloomController
{
public:
	BloomController();
	~BloomController();

	void Draw(LPDIRECT3DTEXTURE9 targetTexture = NULL);
	void SetPower(float power1, float power2, float power3);
	void SetThrethold(float threthold1, float threthold2, float threthold3);

	static const float DefaultPower;
	static const float DefaultThrethold;

private:
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

	float bloomPower[3];
	float bloomThrethold[3];
};

#endif