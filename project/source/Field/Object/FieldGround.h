//=====================================
//
//FieldGround.h
//機能:フィールド地面
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDGROUND_H_
#define _FIELDGROUND_H_

#include "../../../main.h"

class BoardPolygon;

namespace Field
{
	/**************************************
	前方宣言	
	***************************************/

	/**************************************
	クラス定義
	***************************************/
	class FieldGround : public GameObject
	{
	public:
		FieldGround();
		~FieldGround();

		void Draw();

	private:
		BoardPolygon * polygon;
	};
}
#endif