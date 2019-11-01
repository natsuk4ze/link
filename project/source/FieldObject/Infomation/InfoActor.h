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
#include "../../../Framework/Renderer3D/Viewer3D.h"

//**************************************
// クラス定義
//**************************************
class InfoActor :
	public BillboardObject
{
protected:
	Viewer3D* viewer;	// 3D表示処理

	static const D3DXVECTOR2 ViewerWorldSize;
	static const DWORD ViewerCanvasSize;

public:
	InfoActor(const D3DXVECTOR3& pos);
	virtual ~InfoActor();

	// 更新、描画用純粋仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
#endif