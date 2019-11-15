//=============================================================================
//
// 
// 
//
//=============================================================================
#include "../../../../main.h"
#include "BeatGameViewerOrigin.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include"../../../../Framework/Math/Easing.h"


#ifdef _DEBUG

#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Input/input.h"

#endif

static const char* TexturePath[2]
{
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/Success.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/Fail.png",
};

//*****************************************************************************
// 
//*****************************************************************************
BeatGameViewerOrigin::BeatGameViewerOrigin() :
	ExpandPercent(0.0f)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 
	D3DXCreateTextureFromFile(Device, TexturePath[0], &SuccessTexture);
	D3DXCreateTextureFromFile(Device, TexturePath[1], &FailTexture);

	Viewer = new BaseViewerDrawer();
	Viewer->size = D3DXVECTOR3(SCREEN_WIDTH, 240.0f, 0.0f);
	Viewer->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Viewer->position = D3DXVECTOR3((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2, 0.0f);
	Viewer->MakeVertex();
	Viewer->texture = SuccessTexture;

	SetVertex();
}

//*****************************************************************************
// 
//*****************************************************************************
BeatGameViewerOrigin::~BeatGameViewerOrigin()
{
	if (Viewer->texture == SuccessTexture)
	{
		SAFE_RELEASE(FailTexture);
	}
	else
	{
		SAFE_RELEASE(SuccessTexture);
	}
	SAFE_DELETE(Viewer);
}

//=============================================================================
//
//=============================================================================
void BeatGameViewerOrigin::Update()
{
	if (!DrawFlag)
		return;

	TextureExpand();
	SetVertex();
}

//=============================================================================
//
//=============================================================================
void BeatGameViewerOrigin::Draw(void)
{
	if (!DrawFlag)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Device->SetRenderState(D3DRS_ALPHAREF, 0);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	//
	Viewer->Draw();

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// 
//=============================================================================
void BeatGameViewerOrigin::SetVertex()
{
	Viewer->vertexWk[0].vtx = D3DXVECTOR3(0.0f, Viewer->position.y - Viewer->size.y, 0.0f);
	Viewer->vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH * ExpandPercent, Viewer->position.y - Viewer->size.y, 0.0f);
	Viewer->vertexWk[2].vtx = D3DXVECTOR3(0.0f, Viewer->position.y + Viewer->size.y, 0.0f);
	Viewer->vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH * ExpandPercent, Viewer->position.y + Viewer->size.y, 0.0f);
}

//=============================================================================
// 
//=============================================================================
void BeatGameViewerOrigin::TextureExpand(void)
{
	CountFrame++;

	ExpandPercent = Easing::EaseValue((float)CountFrame / 30.0f, 0.0f, 1.0f, InCubic);

	if (ExpandPercent >= 1.0f)
	{
		ExpandPercent = 1.0f;
	}

	//
	{
		Callback();
		DrawFlag = false;
	}
}

//=============================================================================
// 
//=============================================================================
void BeatGameViewerOrigin::DrawStart(bool IsSuccess, std::function<void(void)> Callback)
{
	DrawFlag = true;
	this->Callback = Callback;

	if (IsSuccess)
	{
		Viewer->texture = SuccessTexture;
	}
	else
	{
		Viewer->texture = FailTexture;
	}
}