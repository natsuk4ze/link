//=====================================
//
//クロスブラーフィルターヘッダ[CrossBlurFilter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CROSSBLURFILTER_H_
#define _CROSSBLURFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class CrossBlurFilter : public ScreenObject
{
public:
	CrossBlurFilter(DWORD width, DWORD height);
	~CrossBlurFilter();
	void DrawEffect(UINT pass);

private:
	LPD3DXEFFECT effect;
	D3DXHANDLE hTexelU, hTexelV;
};

#endif