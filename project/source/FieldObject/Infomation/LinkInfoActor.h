//=====================================
//
// リンクインフォアクター[LinkInfoActor.h]
// 機能：町のリンクレベルを表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _LINKINFOACTOR_H_
#define _LINKINFOACTOR_H_

#include "InfoActor.h"

//**************************************
// クラス定義
//**************************************
class LinkInfoActor :
	public InfoActor
{
private:
	static const int MaxDigit = 2;
	int linkLevel;
	int digit[MaxDigit];

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

