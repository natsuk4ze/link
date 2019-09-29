//=====================================
//
//ストロングブラーフィルタヘッダ[StrongBlurFilter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STRONGBLURFILTER_H_
#define _STRONGBLURFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class StrongBlurFilter : public ScreenObject
{
public:	
	StrongBlurFilter();									//コンストラクタ
	~StrongBlurFilter();								//デストラクタ
	void DrawEffect(UINT pass);							//描画処理
	void SetSurfaceSize(float widht, float height);		//サーフェイスサイズ設定処理

private:
	LPD3DXEFFECT effect;								//シェーダ
	D3DXHANDLE hTexelU, hTexelV;						//ハンドル
};

#endif