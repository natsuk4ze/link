//=====================================
//
// ModelViewScene.h
// 機能:モデル確認シーン
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MODELVIEWSCENE_H_
#define _MODELVIEWSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class PlaceActor;

namespace Field
{
	class FieldSkyBox;
}

/**************************************
クラス定義
***************************************/
class ModelViewScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

private:
	std::vector<PlaceActor*> actorContainer;
	Field::FieldSkyBox *skybox;
};

#endif