//=====================================
//
//パーティクルレンダラーヘッダ[ParticleRenderer.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PARTICLERENDERER_H_
#define _PARTICLERENDERER_H_

#include "../../main.h"
#include <vector>

/**************************************
マクロ定義
***************************************/
#define PARTICLE_NUM_MAX	(2048)

/**************************************
前方宣言
***************************************/
class BaseParticle;

/**************************************
クラス定義
***************************************/
class ParticleRenderer
{
public:
	ParticleRenderer();
	~ParticleRenderer();

	void BeginDraw();
	void EndDraw();

	void BeginPass(DWORD pass);
	void EndPass();

	UINT EmbedTransform(const std::vector<BaseParticle*> container);
	UINT EmbedUV(const std::vector<BaseParticle*> container);

private:
	LPDIRECT3DVERTEXDECLARATION9 declare;
	LPD3DXEFFECT effect;
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	LPDIRECT3DVERTEXBUFFER9 transformBuff, uvBuff;
	D3DXHANDLE hMtxView, hMtxProjection, hMtxInvView;

	void LoadEffect();
	void MakeDeclaration();
	void MakeTransformBuffer();
	void MakeUVBuffer();
	void MakeIndexBuffer();
};

#endif