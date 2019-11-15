//=============================================================================
//
//
//
//
//=============================================================================
#ifndef _BeatGameViewerOrigin_H_
#define _BeatGameViewerOrigin_H_

#include <functional>

//*****************************************************************************
// 
//*****************************************************************************
class BaseViewerDrawer;


//*****************************************************************************
// 
//*****************************************************************************
class BeatGameViewerOrigin
{
private:
	int CountFrame;
	float ExpandPercent;
	bool DrawFlag;
	std::function<void(void)> Callback;

	BaseViewerDrawer* Viewer;
	LPDIRECT3DTEXTURE9 SuccessTexture;
	LPDIRECT3DTEXTURE9 FailTexture;

	void SetVertex();
	void TextureExpand();

public:
	BeatGameViewerOrigin();
	~BeatGameViewerOrigin();
	void Update(void);
	void Draw(void);
	void DrawStart(bool IsSuccess, std::function<void(void)> Callback);
};

#endif
