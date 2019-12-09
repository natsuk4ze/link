//=============================================================================
//
// テクスチャ描画クラス [TextureDrawer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "TextureDrawer.h"
#include "../../../../Framework/Math/Easing.h"

//=============================================================================
// コンストラクタ(分割ないテクスチャ用)
//=============================================================================
TextureDrawer::TextureDrawer(D3DXVECTOR2 Size, bool Visible) :
	DestScale(1.0f),
	Devide(D3DXVECTOR2(1.0f, 1.0f)),
	UnitUV(D3DXVECTOR2(1.0f, 1.0f)),
	Index(D3DXVECTOR2(0.0f, 0.0f))
{
	this->Size = Size;
	this->Visible = Visible;
	MakeVertex();
}

//=============================================================================
// コンストラクタ(分割あるテクスチャ用)
//=============================================================================
TextureDrawer::TextureDrawer(D3DXVECTOR2 Size, int DevideX, int DevideY, bool Visible) :
	DestScale(1.0f),
	Devide(D3DXVECTOR2((float)DevideX, (float)DevideY)),
	UnitUV(D3DXVECTOR2(1.0f / DevideX, 1.0f / DevideY)),
	Index(D3DXVECTOR2(0.0f, 0.0f))
{
	this->Size = D3DXVECTOR2(Size.x / DevideX, Size.y / DevideY);
	this->Visible = Visible;
	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
TextureDrawer::~TextureDrawer()
{
	SAFE_RELEASE(Texture);
}

//=============================================================================
// 更新処理
//=============================================================================
void TextureDrawer::Update()
{
	if (!InMove && !InScale &&
		!InExpand && !InClose &&
		!InFade)
		return;

	CountFrame++;
	float Time = (float)CountFrame / Duration;

	// 移動処理
	if (InMove)
	{
		Position = Easing::EaseValue(Time, StartPos, DestPos, easeType);
		SetVertex();

		if (CountFrame >= Duration)
		{
			StartPos = DestPos;
			InMove = false;
			if (Callback != nullptr)
				Callback();
		}
	}

	// 拡大、縮小
	if (InScale)
	{
		Size = Easing::EaseValue(Time, StartSize, StartSize * DestScale, easeType);
		SetVertex();

		if (CountFrame >= Duration)
		{
			StartSize = Size;
			InScale = false;
			if (Callback != nullptr)
				Callback();
		}
	}

	// フェイド
	if (InFade)
	{
		float Alpha = Easing::EaseValue(Time, StartAlpha, DestAlpha, EaseType::Linear);
		SetAlpha(Alpha);

		if (CountFrame >= Duration)
		{
			StartAlpha = DestAlpha;
			InFade = false;
			if (Callback != nullptr)
				Callback();
		}
	}

	// 展開
	if (InExpand)
	{
		if (expandType == ExpandType::LeftToRight)
		{
			Expand_LeftToRight(Time);
		}
		else if (expandType == ExpandType::RightToLeft)
		{
			Expand_RightToLeft(Time);
		}
		else if (expandType == ExpandType::ExpandUpToDown)
		{
			Expand_UpToDown(Time);
		}
		else if (expandType == ExpandType::ExpandDownToUp)
		{
			Expand_DownToUp(Time);
		}
		else if (expandType == ExpandType::ToUpDown)
		{
			Expand_ToUpDown(Time);
		}
		else if (expandType == ExpandType::ToLeftRight)
		{
			Expand_ToLeftRight(Time);
		}

		if (CountFrame >= Duration)
		{
			InExpand = false;
			if (Callback != nullptr)
				Callback();
		}
	}

	// 終了
	if (InClose)
	{
		if (closeType == CloseType::FromUpDown)
		{
			Close_FromUpDown(Time);
		}
		else if (closeType == CloseType::FromLeftRight)
		{
			Close_FromLeftRight(Time);
		}
		else if (closeType == CloseType::CloseLeftToRight)
		{
			Close_LeftToRight(Time);
		}
		else if (closeType == CloseType::CloseRightToLeft)
		{
			Close_RightToLeft(Time);
		}
		else if (closeType == CloseType::CloseUpToDown)
		{
			Close_UpToDown(Time);
		}
		else if (closeType == CloseType::CloseDownToUp)
		{
			Close_DownToUp(Time);
		}

		if (CountFrame >= Duration)
		{
			Visible = false;
			InClose = false;
			if (Callback != nullptr)
				Callback();
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void TextureDrawer::MakeVertex()
{
	// 頂点座標の設定
	SetVertex();

	// テクスチャのパースペクティブコレクト用
	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	// テクスチャ色の設定
	SetColor(SET_COLOR_NOT_COLORED);

	// テクスチャ座標の設定
	SetTexture();
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void TextureDrawer::SetVertex()
{
	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);
}

//=============================================================================
// テクスチャUV設定処理
//=============================================================================
void TextureDrawer::SetTexture(void)
{
	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ展開演出処理
//=============================================================================
void TextureDrawer::Expand_LeftToRight(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, -UnitUV.x, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x + TexPercent, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x + TexPercent, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ展開演出処理
//=============================================================================
void TextureDrawer::Expand_RightToLeft(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, UnitUV.x, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ展開演出処理
//=============================================================================
void TextureDrawer::Expand_UpToDown(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, -UnitUV.y, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y + TexPercent);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y + TexPercent);
}

//=============================================================================
// テクスチャ展開演出処理
//=============================================================================
void TextureDrawer::Expand_DownToUp(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, UnitUV.y, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y + TexPercent);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y + TexPercent);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ展開演出処理
//=============================================================================
void TextureDrawer::Expand_ToUpDown(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, 0.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, UnitUV.y / 2, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y + TexPercent);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y + TexPercent);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y - TexPercent);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y - TexPercent);
}

//=============================================================================
// テクスチャ展開演出処理
//=============================================================================
void TextureDrawer::Expand_ToLeftRight(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, 0.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, UnitUV.x / 2, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x - TexPercent, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x - TexPercent, (Index.y + 1) * UnitUV.y);
}


//=============================================================================
// テクスチャ終了処理
//=============================================================================
void TextureDrawer::Close_FromUpDown(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, 0.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, 0.5f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y + (UnitUV.y * TexPercent));
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y + (UnitUV.y * TexPercent));
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y - (UnitUV.y * TexPercent));
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y - (UnitUV.y * TexPercent));
}

//=============================================================================
// テクスチャ終了処理
//=============================================================================
void TextureDrawer::Close_FromLeftRight(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, 0.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, 0.5f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x + (UnitUV.x * TexPercent), Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x - (UnitUV.x * TexPercent), Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x + (UnitUV.x * TexPercent), (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x - (UnitUV.x * TexPercent), (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ終了処理
//=============================================================================
void TextureDrawer::Close_LeftToRight(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, -1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, UnitUV.x, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ終了処理
//=============================================================================
void TextureDrawer::Close_RightToLeft(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, -1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, -UnitUV.x, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x + TexPercent, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x + TexPercent, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ終了処理
//=============================================================================
void TextureDrawer::Close_UpToDown(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, -1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, UnitUV.y, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y + TexPercent);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y + TexPercent);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ終了処理
//=============================================================================
void TextureDrawer::Close_DownToUp(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, -1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, -UnitUV.y, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y + TexPercent);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y + TexPercent);
}

//=============================================================================
// テクスチャ移動
//=============================================================================
void TextureDrawer::Move(float Duration, D3DXVECTOR3 GoalPos, EaseType Type, std::function<void(void)> callback)
{
	InMove = true;
	CountFrame = 0;
	this->Duration = Duration;
	StartPos = Position;
	DestPos = GoalPos;
	easeType = Type;
	Callback = callback;
}

//=============================================================================
// フェイド処理
//=============================================================================
void TextureDrawer::Fade(float Duration, float DestAlpha, std::function<void(void)> callback)
{
	D3DXCOLOR Color = Vertex[0].diffuse;
	InFade = true;
	CountFrame = 0;
	this->Duration = Duration;
	StartAlpha = Color.a;
	this->DestAlpha = DestAlpha;
	Callback = callback;
}

//=============================================================================
// テクスチャ展開
//=============================================================================
void TextureDrawer::Expand(float Duration, ExpandType expandType, EaseType Type, std::function<void(void)> callback)
{
	InExpand = true;
	Visible = false;
	CountFrame = 0;
	this->Duration = Duration;
	this->expandType = expandType;
	easeType = Type;
	Callback = callback;
}

//=============================================================================
// テクスチャ表示終了
//=============================================================================
void TextureDrawer::Close(float Duration, CloseType closeType, EaseType Type, std::function<void(void)> callback)
{
	InClose = true;
	Visible = true;
	CountFrame = 0;
	this->Duration = Duration;
	this->closeType = closeType;
	easeType = Type;
	Callback = callback;
}

//=============================================================================
// 描画座標設定
//=============================================================================
void TextureDrawer::SetPosition(D3DXVECTOR3 Pos)
{
	Position = Pos;
	SetVertex();
}

//=============================================================================
// 描画UV設定
//=============================================================================
void TextureDrawer::SetIndex(int Index)
{
	this->Index.x = (float)(Index % (int)Devide.x);
	this->Index.y = (float)(Index / (int)Devide.x);
	SetTexture();
}

//=============================================================================
// 描画UV設定
//=============================================================================
void TextureDrawer::SetIndex(int x, int y)
{
	this->Index.x = (float)x;
	this->Index.y = (float)y;
	SetTexture();
}

//=============================================================================
// サイズ設定
//=============================================================================
void TextureDrawer::SetScale(float Scale)
{
	Size *= Scale;
	SetVertex();
}

//=============================================================================
// テクスチャ拡大、縮小
//=============================================================================
void TextureDrawer::SetScale(float Duration, float Scale, EaseType Type, std::function<void(void)> callback)
{
	InScale = true;
	CountFrame = 0;
	this->Duration = Duration;
	StartSize = Size;
	DestScale = Scale;
	easeType = Type;
	Callback = callback;
}