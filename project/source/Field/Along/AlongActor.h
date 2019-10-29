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

		void SetPosition(const D3DXVECTOR3& position) override;

	protected:
		static const float RangePositionOffset;
		static const float MinScale;
		static const float MaxScale;

		MeshContainer * mesh;
	};
}

#endif