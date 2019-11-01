#ifndef _INFOCONTROLLER_H_
#define _INFOCONTROLLER_H_

#include <map>
#include "Infomation/LinkInfoActor.h"

class InfoController
{
private:			// リンクレベル表示用

public:
	InfoController();
	~InfoController();

	void Update();
	void Draw();

	void SetLinkLevel(int x, int y, int townLevel);
};

#endif
