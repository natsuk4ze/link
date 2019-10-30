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
#include "../../../Framework/Renderer3D/BoardPolygon.h"

//**************************************
// クラス定義
//**************************************
class InfoActor :
	public BillboardObject
{
protected:
	//*******継承先で使用********
	BoardPolygon* polygon;
	//***************************
	int linkLevel;
	//bool onCamera;

	static const float ActorSize;

public:
	InfoActor(const D3DXVECTOR3& pos, const int& level);
	virtual ~InfoActor();

	// 更新、描画
	virtual void Update();
	virtual void Draw();

	// レベル変更時使用
	void SetLevel(const int& nextLevel);
};

#endif