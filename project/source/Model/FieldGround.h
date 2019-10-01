//=====================================
//
//FieldGround.h
//機能:フィールド地面
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDGROUND_H_
#define _FIELDGROUND_H_

#include "../../main.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldGround : public BoardPolygon, public GameObject
{
public:
	FieldGround();
	~FieldGround();

	void Draw();
};

#endif