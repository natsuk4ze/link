//=====================================
//
//ショックブラーヘッダ[ShockBlur.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SHOCKBLUR_H_
#define _SHOCKBLUR_H_

#include "../../../main.h"
#include "../ScreenObject.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ShockBlur : public ScreenObject
{
public:
	ShockBlur();
	~ShockBlur();
	void DrawEffect();
	void SetPower(float power);
	void SetCenterPos(D3DXVECTOR3 pos);
	void SetSurfaceSize(float widht, float height);

private:
	LPD3DXEFFECT effect;				//シェーダ
	D3DXHANDLE hndlPower, hndlCenter;	//各ハンドル
	D3DXHANDLE hndlTU, hndlTV;			//各ハンドル
};

#endif