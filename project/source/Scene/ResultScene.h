//=====================================
//
//ResultScene.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class ResultScene : public BaseScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
#endif