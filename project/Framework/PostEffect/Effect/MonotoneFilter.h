//=====================================
//
//モノトーンフィルタヘッダ[MonotoneFilter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MONOTONEFILTER_H_
#define _MONOTONEFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class MonotoneFilter : ScreenObject {
public:
	MonotoneFilter(DWORD width, DWORD height);
	~MonotoneFilter();

	void Draw();									//描画処理
	void SetPower(float power);						//強さ設定処理

private:
	LPD3DXEFFECT effect;							//シェーダ
	D3DXHANDLE hndlPower;							//各ハンドル
};

#endif