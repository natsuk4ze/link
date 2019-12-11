//=====================================
//
//BoothController.h
//機能:ブースコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOOTHCONTROLLER_H_
#define _BOOTHCONTROLLER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
前方宣言
***************************************/
class SerialWrapper;

/**************************************
クラス定義
***************************************/
class BoothController : public BaseSingleton<BoothController>
{
public:
	void Init();
	void Uninit();

	void RotateTable(char angle);

	void BlinkLED(bool isPlus);

private:
	SerialWrapper * serial;

	BoothController() {};
	BoothController(const BoothController&) {};
	friend class BaseSingleton<BoothController>;
};
#endif