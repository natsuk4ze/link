#ifndef _GUIDEVIEWERBG_H_
#define _GUIDEVIEWERBG_H_

#include "../../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../../Framework/Core/GameObject.h"

class GuideViewerBG :
	public GameObject
{
private:
	BoardPolygon* polygon;
public:
	GuideViewerBG();
	~GuideViewerBG();

	void Update();
	void Draw();
};

#endif
