//=====================================
//
//トランスフォームオブジェクトヘッダ[TransformObject.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TRANSFORMOBJECT_H_
#define _TRANSFORMOBJECT_H_

#include "../../main.h"
#include "MeshContainer.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class TransformObject : public GameObject
{
public:
	TransformObject();
	~TransformObject();

	void Draw();

private:
	MeshContainer *mesh;
};

#endif