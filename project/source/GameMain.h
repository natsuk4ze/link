//=====================================
//
//GameMain.h
//機能:ゲームメイン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "../main.h"
#include "../Framework/Core/BaseGame.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameMain : public BaseGame
{
public:
	GameMain(HINSTANCE hInstance, HWND hWnd);

	void Update() override;
};
#endif