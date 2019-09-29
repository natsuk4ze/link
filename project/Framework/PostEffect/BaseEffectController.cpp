//=====================================
//
//テンプレート処理[BaseEffectController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BaseEffectController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
デフォルトターゲット設定処理
***************************************/
void BaseEffectController::SetDefaultTarget(LPDIRECT3DTEXTURE9 texture)
{
	defaultTarget = texture;
}