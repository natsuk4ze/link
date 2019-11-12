//=====================================
//
// ゲームサブ[GameSub.h]
// 機能：サブウインドウ
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GAMESUB_H_
#define _GAMESUB_H_

#include "../../main.h"
#include "../../Framework/Core/BaseGame.h"

//**************************************
// クラス定義
//**************************************
class GameSub :
	public BaseGame
{
	GameSub(HINSTANCE hInstance, HWND hWnd);

	void Update()override;
};

#endif

