//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"

/**************************************
グローバル変数
***************************************/
void GameParticleManager::Init()
{
	controllers.resize(ParticleID::Max, NULL);
}
