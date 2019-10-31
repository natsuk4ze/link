//=====================================
//
// インフォディジット[InfoDigit.h]
// 機能：情報表示用数字
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _INFODIGIT_H_
#define _INFODIGIT_H_

#include "../../../Framework/Renderer2D/Polygon2D.h"
//**************************************
// クラス定義
//**************************************
class InfoDigit :
	public Polygon2D
{
private:
	int num;

	static const int divideX, divideY;	// 分割数
	static const float width, height;	// 幅、高さ

public:
	InfoDigit(const int& num, const D3DXVECTOR3& pos);
	~InfoDigit();

	void Update();

	// 表示する数字の変更
	void ChangeDigit(const int& num);
};

#endif
