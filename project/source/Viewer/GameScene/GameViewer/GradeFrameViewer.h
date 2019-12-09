//=============================================================================
//
// グレードフレームクラス [GradeFrameViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _GradeFrameViewer_H_
#define _GradeFrameViewer_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GradeFrameViewer : public BaseViewer
{
private:
	TextureDrawer* FrameUp;
	TextureDrawer* FrameDown;
	std::function<void(void)> Callback;


public:
	GradeFrameViewer();
	~GradeFrameViewer();
	void Update(void);
	void Draw(void);
	void SlideIn(std::function<void(void)> callback = nullptr);
	void SlideOut(std::function<void(void)> callback = nullptr);
};

#endif
