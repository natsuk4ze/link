#include "CRTFilter.h"
#include "../../Resource/ResourceManager.h"
#include "../../Math/TMath.h"

const int CRTFilter::LoopTime = 120;

CRTFilter::CRTFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	const char* Path = "data/Effect/CRTFilter.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);
	Path = "data/Effect/WhiteNoise.png";
	ResourceManager::Instance()->GetTexture(Path, whiteNoise);

	effect->SetTechnique("tech");
	hndlTime = effect->GetParameterByName(0, "Time");
	hndlScreen = effect->GetParameterByName(0, "ScreenParams");
}

CRTFilter::~CRTFilter()
{
	SAFE_RELEASE(effect);
}

void CRTFilter::Draw(UINT pass)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetTexture(1, whiteNoise);

	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

void CRTFilter::SetTime()
{
	time++;
	time = Math::WrapAround(0, LoopTime, time);
	effect->SetFloat(hndlTime, (float)time / 120.0f);
}

void CRTFilter::SetScreenParam(float width, float height)
{
	float buff[2] = { width, height };
	effect->SetFloatArray(hndlScreen, buff, 2);
}
