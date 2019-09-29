//=====================================
//
//ビルボードトランスフォームヘッダ[BillboardTransform.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BILLBOARDTRANSFORM_H_
#define _BILLBOARDTRANSFORM_H_

#include "../Core/Transform.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BillboardTransform : public Transform
{
	using Transform::Transform;
public:
	//ワールド変換設定処理
	virtual void SetWorld(const D3DXMATRIX* parent = NULL) const override;
	virtual D3DXMATRIX GetMatrix() const override;
};

#endif