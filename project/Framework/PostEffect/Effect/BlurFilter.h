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

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BlurFilter : public ScreenObject {
public:
	BlurFilter();
	~BlurFilter();
	void DrawEffect(UINT pass);							//描画処理
	void SetSurfaceSize(float width, float height);		//サーフェイスサイズ設定処理

private:
	LPD3DXEFFECT effect;								//シェーダ
	D3DXHANDLE texelU, texelV;							//各ハンドル
};

#endif