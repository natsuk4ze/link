//=====================================
//
//シーンパーティクルマネージャヘッダ[SceneParticleManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCENEPARTICLEMANAGER_H_
#define _SCENEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../PostEffect/ScreenObject.h"
#include "BaseParticleController.h"
#include <vector>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SceneParticleManager
{
public:
	SceneParticleManager();

	//初期化、終了、更新、描画処理
	virtual void Init() = 0;
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	//パーティクル発生処理
	virtual BaseEmitter* Generate(UINT id, const D3DXVECTOR3& pos);
	virtual BaseEmitter* Generate(UINT id, const Transform& transform);

protected:
	//レンダーターゲット関連
	LPDIRECT3DTEXTURE9 renderTexture;
	LPDIRECT3DSURFACE9 renderSurface;
	D3DVIEWPORT9 viewPort;
	ScreenObject *screenObj;

	//キャッシュ用
	LPDIRECT3DSURFACE9 oldSuf;
	D3DVIEWPORT9 oldViewport;

	//パーティクルコントローラコンテナ
	std::vector<BaseParticleController*> controllers;

	//描画準備
	void CreateRenderTarget(void);
	void ChangeRenderParameter(void);
	void RestoreRenderParameter(void);

private:
	bool initialized;
};
#endif