//=====================================
//
//AlongActor.h
//機能:道沿いのアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ALONGACTOR_H_
#define _ALONGACTOR_H_

#include "../../../main.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;

namespace Field::Along
{
	/**************************************
	クラス定義
	***************************************/
	class AlongActor : public GameObject
	{
	public:
		AlongActor();
		~AlongActor();

		void Update();
		void Draw(const D3DXMATRIX& parent);

		void PlayAnimation();

	protected:
		MeshContainer * mesh;
	};
}

#endif