//=====================================
//
//ベースパーティクルコントローラヘッダ[BaseParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEPARTICLECONTROLLER_H_
#define _BASEPARTICLECONTROLLER_H_

#include "../../main.h"
#include "BaseParticle.h"
#include "BaseEmitter.h"
#include "ParticleJsonParser.h"
#include "ParticleRenderer.h"

#include <vector>
#include <functional>

/**************************************
マクロ定義
***************************************/

/**************************************
前方宣言
***************************************/
class ParticleRenderer;
class ParticleUnit;

/**************************************
BasePartlceControllerクラス
継承先で
・単位頂点バッファ作成、テクスチャ読み込み
・void MakeParticleContainer(), MakeEmitterContainer()
を実装する
***************************************/
class BaseParticleController
{
public:
	enum ParticleType
	{
		Particle_3D = 0,
		Particle_2D,
		Max
	};

	//コンストラクタ、デストラクタ
	BaseParticleController(ParticleType type);
	virtual ~BaseParticleController();

	template<class T>
	BaseParticleController(const T& src, const ParticleJsonParser& data) :
		unitBuff(NULL), texture(NULL)
	{
		if (!mRenderer)
		{
			mRenderer.reset(new ParticleRenderer());
		}
		renderer = mRenderer;

		//テクスチャロード
		LoadTexture(data.GetTexturePath().c_str());

		//単位頂点バッファ作成
		MakeUnitBuffer(data.GetSize(), data.GetTexDiv());

		//パーティクルコンテナ作成
		particleContainer.resize(data.GetParticleMax());
		for (auto&& particle : particleContainer)
		{
			particle = new T();
		}

		//エミッタコンテナ作成
		MakeEmitterContainer(data);

	};

	//エミッタセット処理
	virtual BaseEmitter* SetEmitter(const D3DXVECTOR3& pos, std::function<void(void)>& callback);
	virtual BaseEmitter* SetEmitter(const Transform& transform, std::function<void(void)>& callback);

	virtual void Uninit();				//終了処理
	void Update();						//更新処理
	bool Draw();						//描画処理

	//描画開始・終了処理
	static void BeginDraw();		
	static void EndDraw();			

	//描画パーティクル数取得処理
	unsigned GetParticleCount() const;

protected:
	LPDIRECT3DVERTEXBUFFER9 unitBuff;				//単位頂点バッファ
	LPDIRECT3DTEXTURE9 texture;						//テクスチャ
	std::vector<BaseParticle*> particleContainer;	//パーティクルコンテナ
	std::vector<BaseEmitter*> emitterContainer;		//エミッタコンテナ
	std::shared_ptr<ParticleRenderer> renderer;		//レンダラー

	unsigned particleCount;							//描画パーティクル数

	//単位頂点バッファ作成処理
	void MakeUnitBuffer(const D3DXVECTOR2& size, const D3DXVECTOR2& texDix = D3DXVECTOR2(1.0f, 1.0f));	
	void LoadTexture(const char* filePath);			//テクスチャ読み込み処理

	//コンテナ作成
	virtual void MakeEmitterContainer(const ParticleJsonParser& data);

	//使用するパーティクルのタイプ
	ParticleType useType;

private:
	//インスタンシングに必要な静的メンバ
	static std::shared_ptr<ParticleRenderer> mRenderer;
};

/**************************************
パーティクルの単位頂点
***************************************/
class ParticleUnit
{
public:
	D3DXVECTOR3 vtx;	//頂点座標
	D3DXVECTOR2 tex;	//UV座標
};

#endif