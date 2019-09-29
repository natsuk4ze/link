//=====================================
//
//基底シーンヘッダ[BaseScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASESCENE_H_
#define _BASESCENE_H_

/**************************************
マクロ定義
***************************************/

/**************************************
BaseSceneクラス
継承先で
void Init()
void Uninit()
void Update()
void Draw()
を実装する
***************************************/
class BaseScene
{
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif