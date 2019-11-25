//=====================================
//
// タイトルロゴ[TitleLogo.h]
// 機能：タイトルロゴ表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "../../../Framework/Renderer2D/Polygon2D.h"
//**************************************
// クラス定義
//**************************************
class TitleLogo :
	public Polygon2D
{
private:
	static const D3DXVECTOR3 InitPos;
	static const D3DXVECTOR2 InitSize;

public:
	TitleLogo();
	~TitleLogo();

	void Update();
	void Draw();

};

#endif

