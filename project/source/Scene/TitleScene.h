//=====================================
//
//TitleScene.h
//機能:タイトルシーン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TitleScene_H_
#define _TitleScene_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TitleScene : public BaseScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
#endif