//=====================================
//
//BoothController.cpp
//‹@”\:
//Author:GP12B332 21 —§‰Ô—Y‘¾
//
//=====================================
#include "BoothController.h"
#include "../../Framework/Serial/SerialWrapper.h"

/**************************************
‰Šú‰»ˆ—
***************************************/
void BoothController::Init()
{
	serial = new SerialWrapper(3);
	serial->Begin(9600);
}

/**************************************
Žæ“¾ˆ—
***************************************/
void BoothController::Uninit()
{
	SAFE_DELETE(serial);
}

/**************************************
‰ñ“]ˆ—
***************************************/
void BoothController::RotateTable(unsigned char angle)
{
	size_t numPut = serial->Write(angle);
}

/**************************************
LED“_–Åˆ—
***************************************/
void BoothController::BlinkLED(bool isPlus)
{
	if (isPlus)
		serial->Write('p');
	else
		serial->Write('m');
}
