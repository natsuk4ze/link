#ifndef _CRTFILTER_H_
#define _CRTFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"

class CRTFilter :
	public ScreenObject
{
public:
	CRTFilter(DWORD width, DWORD height);
	~CRTFilter();

	void Draw(UINT pass);
	void SetTime();
	void SetScreenParam(float width, float height);

private:
	int time;
	LPD3DXEFFECT effect;
	D3DXHANDLE hndlTime;
	D3DXHANDLE hndlScreen;
	LPDIRECT3DTEXTURE9 whiteNoise;

	static const int LoopTime;

};


#endif