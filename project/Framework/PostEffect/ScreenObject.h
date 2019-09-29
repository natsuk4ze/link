//=====================================
//
//スクリーンオブジェクトヘッダ[ScreenObject.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCREENOBJECT_H_
#define _SCREENOBJECT_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ScreenObject {
public:
	ScreenObject();
	virtual ~ScreenObject();

	void Draw();
	void Resize(float width, float height);

private:
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
};
/**************************************
プロトタイプ宣言
***************************************/

#endif