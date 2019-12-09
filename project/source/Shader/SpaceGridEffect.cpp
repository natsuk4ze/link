//=====================================
//
//SpaceGridEffect.cpp
//機能:宇宙グリッドの描画エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpaceGridEffect.h"
#include "../../Framework/Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
SpaceGridEffect::SpaceGridEffect() :
	SpriteEffect("data/Effect/SpaceGridRenderer.cfx")
{
	//ハンドル取得
	hTime = effect->GetParameterByName(0, "time");
	hLumineTex = effect->GetParameterByName(0, "Lumine");

	//テクスチャ読み込み
	ResourceManager::Instance()->GetTexture("data/TEXTURE/Field/spaceGridLumine.jpg", lumineMap);
	effect->SetTexture(hLumineTex, lumineMap);
}

/**************************************
デストラクタ
***************************************/
SpaceGridEffect::~SpaceGridEffect()
{
	SAFE_RELEASE(effect);
}

/**************************************
アルファ値設定処理
***************************************/
void SpaceGridEffect::SetAlpha(float alpha)
{
	diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

/**************************************
時間設定処理
***************************************/
void SpaceGridEffect::SetTime(float t)
{
	effect->SetFloat(hTime, t);
}
