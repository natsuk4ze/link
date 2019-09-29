//=====================================
//
//トランジションコントローラヘッダ[TransitionController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TRANSITIONCONTROLLER_H_
#define _TRANSITIONCONTROLLER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"

#include <vector>
#include <functional>

/**************************************
前方宣言
***************************************/
class Polygon2D;
class BaseTransitionMask;

/**************************************
マクロ定義
***************************************/
enum TransitionType
{
	HexaRotation,
	HexaPop,
	Mist,
	TransitionMax
};

/**************************************
クラス定義
***************************************/
class TransitionController : public BaseSingleton<TransitionController>
{
	friend class BaseSingleton<TransitionController>;

public:
	virtual void Update();
	virtual void DrawMask();
	virtual void DrawTransition();

	virtual bool SetTransition(bool isOut, TransitionType type, std::function<void(void)> callback = NULL);

protected:
	TransitionController();
	~TransitionController();

	std::vector<BaseTransitionMask*> maskContainer;
	Polygon2D* transitionBG;

	std::function<void(void)> callback;
	
	TransitionType usingMask;

	bool isRunning;
	bool isDrawBG;

	
};

#endif