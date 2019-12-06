//=============================================================================
//
// グレードアップクラス [GradeUpViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _GradeUpViewer_H_
#define _GradeUpViewer_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GradeUpViewer : public BaseViewer
{
private:
	TextureDrawer* GradeUpText;
	TextureDrawer* AILevelTex;
	std::function<void(void)> Callback;

	void TextPopUp(void);
	void GradeUpFadeOut(void);
public:
	GradeUpViewer();
	~GradeUpViewer();
	void Update(void);
	void Draw(void);
	void SetGradeUp(std::function<void(void)> Callback = nullptr);
};

#endif
