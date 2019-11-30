//=====================================
//
//MophingTestScene.h
//機能:モーフィングテストシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MOPHINGTESTSCENE_H_
#define _MOPHINGTESTSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class MophingEffect;
class MeshContainer;
class MorphingMeshContainer;

namespace Field
{
	class FieldSkyBox;
}
/**************************************
クラス定義
***************************************/
class MophingTestScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Field::FieldSkyBox *skybox;

	MorphingMeshContainer *morphContainer;
	MeshContainer *mesh;
};
#endif