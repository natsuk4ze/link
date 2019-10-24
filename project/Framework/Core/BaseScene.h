//=====================================
//
//基底シーンヘッダ[BaseScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASESCENE_H_
#define _BASESCENE_H_

#include "../Camera/Camera.h"

/**************************************
前方宣言
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
	BaseScene(LPDIRECT3DTEXTURE9 renderTexture, LPDIRECT3DSURFACE9 renderSurface);
	~BaseScene();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	Camera * sceneCamera;
	LPDIRECT3DTEXTURE9 renderTexture;
	LPDIRECT3DSURFACE9 renderSurface;
};

#endif