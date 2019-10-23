//=====================================
//
//ブラーフィルターヘッダ[BlurFilter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLURFILTER_H_
#define _BLURFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"
#include <vector>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BlurFilter : public ScreenObject {
public:
	BlurFilter(DWORD width, DWORD height);
	~BlurFilter();
	void DrawEffect(UINT pass);							//描画処理

private:
	static const int SizeTexelArray;

	LPD3DXEFFECT effect;								//シェーダ
	D3DXHANDLE texelU, texelV;							//各ハンドル

	std::vector<float> offsetTexelU;
	std::vector<float> offsetTexelV;
};

#endif