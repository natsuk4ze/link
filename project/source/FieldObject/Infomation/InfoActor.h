//=====================================
//
// インフォアクター[InfoActor.h]
// 機能：フィールド上に情報を表示するための基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _INFOACTOR_H_
#define _INFOACTOR_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Renderer3D/Viewer3D.h"

//**************************************
// クラス定義
//**************************************
class DigitInfo :
	public Polygon2D
{
private:
	int num;

public:
	DigitInfo(const int& num, const D3DXVECTOR3& pos);
	~DigitInfo();

	void Update();
};

class InfoActor :
	public BillboardObject
{
protected:
	Viewer3D* viewer;	// 3D表示処理
	DigitInfo* digit[2];
	int linkLevel;

	static const float ActorSize;

public:
	InfoActor(const D3DXVECTOR3& pos);
	virtual ~InfoActor();

	// 更新、描画
	virtual void Update();
	virtual void Draw();
};
#endif