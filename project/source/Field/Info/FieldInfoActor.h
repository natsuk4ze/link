//=====================================
//
// フィールドインフォアクター[FieldInfoActor.h]
// 機能：フィールド上の情報を表示するアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _FIELDINFOACTOR_H_
#define _FIELDINFOACTOR_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"

//**************************************
// クラス定義
//**************************************
class FieldInfoActor :
	public BillboardObject
{
private:
	BoardPolygon* polygon;

	static const D3DXVECTOR3 ActorScale;

public:
	FieldInfoActor(const D3DXVECTOR3& pos);
	~FieldInfoActor();

	void Update();
	void Draw();
};

#endif

