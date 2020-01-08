//=============================================================================
//
// スターダストエフェクトクラス [StarDust.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "StarDust.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	StarDustControllerコンストラクタ
	***************************************/
	StarDustController::StarDustController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle{ 2.0f, 2.0f };
		const D3DXVECTOR2 TextureDivine{ (float)StarDust::TexDiv, (float)StarDust::TexDiv };
		MakeUnitBuffer(SizeParticle, TextureDivine);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/levelup.png";
		LoadTexture(Path);

		//エミッタコンテナ作成
		const unsigned MaxParticle = 256;
		const unsigned MaxEmitter = 1;
		const int DurationEmit = 60;
		const int NumEmit = 8;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
			emitter->CreateParticleContainer<StarDust>(MaxParticle);
		}
	}

	/**************************************
	描画
	***************************************/
	bool StarDustController::Draw(void)
	{
		bool Result = false;
		LPDIRECT3DDEVICE9 Device = GetDevice();

		//レンダーステートを加算合成に設定
		//Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		Result = BaseParticleController::Draw();

		//レンダーステートを元に戻す
		//Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		return Result;
	}

	/**************************************
	Emitterの位置を設定
	***************************************/
	void StarDustController::SetEmitterPos(D3DXVECTOR3 Pos)
	{
		for (auto&& emitter : emitterContainer)
		{
			if (emitter->IsActive())
				emitter->SetPosition(Pos);
		}
	}

	/**************************************
	StarDust staticメンバ
	***************************************/
	const int StarDust::MinLife = 10;
	const int StarDust::MaxLife = 15;
	const float StarDust::MinScale = 0.5;
	const float StarDust::MaxScale = 1.0f;
	const int StarDust::TexDiv = 6;

	/**************************************
	StarDustコンストラクタ
	***************************************/
	StarDust::StarDust() :
		Particle3D(MinLife, MaxLife),
		initScale(Math::RandomRange(MinScale, MaxScale)),
		directionMove(Vector3::Random())
	{
		//directionMove.y = Math::RandomRange(0.0f, 0.5f);
		//D3DXVec3Normalize(&directionMove, &directionMove);
	}

	/**************************************
	StarDust初期化処理
	***************************************/
	void StarDust::Init()
	{
		int randomIndex = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = randomIndex % TexDiv * 1.0f / TexDiv;
		uv.v = randomIndex / TexDiv * 1.0f / TexDiv;

		cntFrame = 0;
		active = true;

		//ランダムにZ軸回転
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//移動方向に初期座標をオフセット
		D3DXVECTOR3 InitOffset = D3DXVECTOR3
		(
			Math::RandomRange(-1.0f, 1.0f),
			Math::RandomRange(-1.0f, 1.0f),
			Math::RandomRange(-1.0f, 1.0f)
		) * 7.0f;
		transform->Move(InitOffset);
	}

	/**************************************
	StarDust更新処理
	***************************************/
	void StarDust::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		const float EndScale = 0.0f;
		float scale = Easing::EaseValue(t, initScale, EndScale, EaseType::InQuint);
		transform->SetScale(Vector3::One * scale);

		const float angleRotate = 33.0f;
		//transform->Rotate(0.0f, 0.0f, angleRotate);
	}

}