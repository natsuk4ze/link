//=====================================
//
// ParticleTestScene.h
// 機能:パーティクルテストシーン
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PARTICLETESTSCENE_H_
#define _PARTICLETESTSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
前方宣言
***************************************/
class SkyBox;
class TestParticleManager;
class PlaceActor;
class TestParticleManager;

namespace Field
{
	class FieldGround;
}

/**************************************
クラス定義
***************************************/
class ParticleTestScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Draw();
	void Update();

private:
	SkyBox *skybox;
	Field::FieldGround *ground;
	PlaceActor *actor;
	TestParticleManager* particleManager;
};

#endif