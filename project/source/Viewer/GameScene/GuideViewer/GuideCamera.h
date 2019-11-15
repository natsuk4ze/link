#ifndef _GUIDECAMERA_H_
#define _SUIDECAMERA_H_

#include "../../../../Framework/Camera/Camera.h"

class GuideCamera :
	public Camera
{
private:
	static const float ScreenHeight;
	static const float ScreenWidth;
	static const float InitViewAspect;
public:
	GuideCamera();
	~GuideCamera();
};

#endif