//=====================================
//
//ブルームフィルターヘッダ[BloomFilter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLOOMFILTER_H_
#define _BLOOMFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BloomFilter : public ScreenObject
{
public:
	BloomFilter(DWORD width, DWORD height);
	~BloomFilter();
	void DrawEffect(UINT pass);
	void SetThrethold(float threthold);
	void SetBloomPower(float power);

private:
	LPD3DXEFFECT effect;
	D3DXHANDLE hThrethold;
	D3DXHANDLE hBloomPower;
};

#endif