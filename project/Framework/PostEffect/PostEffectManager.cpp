//=====================================
//
//ポストエフェクトマネージャ処理[PostEffectManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PostEffectManager.h"

#include "BloomController.h"
#include "CrossFilterController.h"
#include "ShockBlurController.h"
#include "SpeedBlurController.h"
#include "SpikeNoiseController.h"

using namespace std;
/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
PostEffectManager::PostEffectManager()
{
	effectContainer.push_back(BloomController::Instance());
	effectContainer.push_back(CrossFilterController::Instance());
	effectContainer.push_back(ShockBlurController::Instance());
	effectContainer.push_back(SpeedBlurController::Instance());
	effectContainer.push_back(SpikeNoiseController::Instance());
}

/**************************************
更新処理
***************************************/
void PostEffectManager::Update()
{
	for (auto&& effect : effectContainer)
	{
		effect->Update();
	}
}
/**************************************
描画処理
***************************************/
void PostEffectManager::Draw()
{
	for (unsigned i = PostEffect::Bloom; i < PostEffect::Max; i++)
	{
		if (!IsUse(i))
			continue;

		//ブルームなどの輝き系は影響が強すぎるので
		//各シーンに描画を任せる
		if (IsBrightEffect(i))
			continue;

		effectContainer[i]->Draw();
	}
}

/**************************************
使用エフェクト設定処理
***************************************/
void PostEffectManager::SetUse(unsigned flgUse)
{
	this->flgUse = flgUse;
}

/**************************************
使用エフェクト判定処理
***************************************/
bool PostEffectManager::IsUse(unsigned flg)
{
	unsigned check = 0x01;
	check = check << (flg);

	return check & flgUse;
}

/**************************************
デフォルトターゲット設定処理
***************************************/
bool PostEffectManager::IsBrightEffect(UINT id)
{
	return id == PostEffect::CrossFilter || id == PostEffect::Bloom;
}

/**************************************
デフォルトターゲット設定処理
***************************************/
void PostEffectManager::PassDefaultTarget(LPDIRECT3DTEXTURE9 target)
{
	for (auto& effect : effectContainer)
	{
		effect->SetDefaultTarget(target);
	}
}