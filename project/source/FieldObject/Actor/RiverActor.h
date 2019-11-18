//=====================================
//
// リバーアクター[RiverActor.h]
// 機能：川（時空断裂）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _RIVERACTOR_H_
#define _RIVERACTOR_H_

#include "PlaceActor.h"
//**************************************
// 前方宣言
//**************************************
namespace Field::Actor
{
	class RiverEffect;
}
//**************************************
// クラス定義
//**************************************
class RiverActor :
	public PlaceActor
{
public:
	enum FlowDirection
	{
		None = -1,
		Forward,
		Right,
		Back,
		Left
	};

	RiverActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~RiverActor();

	void Update() override;
	void Draw() override;

	void SetDirection(FlowDirection direction);

private:
	static const float FlowSpeed;

	FlowDirection direction;
	D3DXVECTOR2 uv;
	Field::Actor::RiverEffect *effect;
};

#endif
