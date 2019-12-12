//=====================================
//
//TimeUpViewer.h
//機能:タイムアップビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TIMEUPVIEWER_H_
#define _TIMEUPVIEWER_H_

#include "../../../../main.h"
#include "../../Framework/BaseViewer.h"
#include <functional>

/**************************************
前方宣言
***************************************/
class TextureDrawer;

/**************************************
クラス定義
***************************************/
class TimeUpViewer : public BaseViewer
{
public:
	TimeUpViewer();
	~TimeUpViewer();

	void Update();
	void Draw();

	void Set(std::function<void()> callback = nullptr);

private:
	TextureDrawer *tex;

	int cntFrame;
	bool active;

	std::function<void()> callback;
};
#endif