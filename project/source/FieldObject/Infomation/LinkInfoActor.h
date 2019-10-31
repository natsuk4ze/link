//=====================================
//
// リンクインフォアクター[LinkInfoActor.h]
// 機能：リンクレベルを表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _LINKINFOACTOR_H_
#define _LINKINFOACTOR_H_

#include "InfoActor.h"
#include "InfoDigit.h"

//**************************************
// クラス定義
//**************************************
class LinkInfoActor :
	public InfoActor
{
private:
	static const int MaxDigit = 2;
	int linkLevel;						// リンクレベル
	int digit[MaxDigit];				// リンクレベルを一桁ごとに分離
	InfoDigit* digitActor[MaxDigit];	// 一桁ごとに表示
	Polygon2D* logo;					// リンクレベルのロゴ表示

public:
	LinkInfoActor(const D3DXVECTOR3& pos, const int& level);
	~LinkInfoActor();

	// 更新、描画
	void Update()override;
	void Draw()override;

	// レベル変更時使用
	void SetLevel(const int& nextLevel);

};

#endif

