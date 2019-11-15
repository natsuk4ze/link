#include "GuideCamera.h"

const float GuideCamera::ScreenHeight = 480.0f;
const float GuideCamera::ScreenWidth = 480.0f;
const float GuideCamera::InitViewAspect = ScreenWidth / ScreenHeight;

GuideCamera::GuideCamera()
{
	viewAspect = InitViewAspect;
}

GuideCamera::~GuideCamera()
{
}
