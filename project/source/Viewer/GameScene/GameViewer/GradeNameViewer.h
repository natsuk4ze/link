//=============================================================================
//
// グレードネームクラス [GradeNameViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _GradeNameViewer_H_
#define _GradeNameViewer_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GradeNameViewer : public BaseViewer
{
private:
	TextureDrawer* GradeTitle;
	TextureDrawer* LineTex;
	std::function<void(void)> Callback;

public:
	GradeNameViewer();
	~GradeNameViewer();
	void Update(void);
	void Draw(void);
};

#endif
