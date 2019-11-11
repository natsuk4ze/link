#ifndef _GUIDEVIEWER_H_
#define _GUIDEVIEWER_H_

#include "GuideActor.h"

class GuideViewer
{
private:
	GuideActor* actor;

public:
	GuideViewer();
	~GuideViewer();

	void Update();
	void Draw();

	void ChangeAnim(GuideActor::AnimState next);
};

#endif
