//=============================================================================
//
// テクスチャ描画クラス [TextureDrawer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _TextureDrawer_H_
#define _TextureDrawer_H_

#include <functional>
#include "BaseTextureDrawer.h"

enum ExpandType
{
	LeftToRight,
	RightToLeft,
	ExpandUpToDown,
	ExpandDownToUp,
	ToUpDown,
	ToLeftRight,
};

enum CloseType
{
	FromUpDown,
	FromLeftRight,
	CloseUpToDown,
	CloseDownToUp,
};


//*****************************************************************************
// クラス定義
//*****************************************************************************
class TextureDrawer : public BaseTextureDrawer
{
private:
	int CountFrame = 0;
	float Duration;			// 間隔
	float DestScale;		// 拡大、縮小時の目標スケール
	float StartAlpha;		// フェイド時の最初アルファ
	float DestAlpha;		// フェイド時の目標アルファ
	D3DXVECTOR3 StartPos;	// 移動時の始点
	D3DXVECTOR3 DestPos;	// 移動時の終点
	D3DXVECTOR2 StartSize;	// 拡大、縮小時の最初スケール
	D3DXVECTOR2 Devide;		// テクスチャの分割数
	D3DXVECTOR2 UnitUV;		// 単位テクスチャのUV座標
	D3DXVECTOR2 Index;		// 表示するテクスチャのインデックス
	EaseType easeType;
	ExpandType expandType;
	CloseType closeType;
	bool InMove = false;
	bool InScale = false;
	bool InExpand = false;
	bool InClose = false;
	bool InFade = false;
	std::function<void(void)> Callback;

	void MakeVertex(void);
	void SetVertex(void);
	void SetTexture(void);
	void Expand_LeftToRight(float Time);
	void Expand_RightToLeft(float Time);
	void Expand_UpToDown(float Time);
	void Expand_DownToUp(float Time);
	void Expand_ToUpDown(float Time);
	void Expand_ToLeftRight(float Time);
	void Close_FromUpDown(float Time);
	void Close_FromLeftRight(float Time);
	void Close_UpToDown(float Time);
	void Close_DownToUp(float Time);
public:
	// 分割ないテクスチャ用
	TextureDrawer(D3DXVECTOR2 TextureSize, bool Visible = true);
	// 分割あるテクスチャ用
	TextureDrawer(D3DXVECTOR2 TextureSize, int DevideX, int DevideY, bool Visible = true);
	~TextureDrawer();

	void Update();
	void SetPosition(D3DXVECTOR3 Pos);
	void SetIndex(int Index);
	void SetIndex(int x, int y);
	void SetScale(float Scale);
	void SetScale(float Duration, float Scale, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Expand(float Duration, ExpandType expandType, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Close(float Duration, CloseType closeType, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Move(float Duration, D3DXVECTOR3 DestPos, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Fade(float Duration, float DestAlpha, std::function<void(void)> callback = nullptr);
};

#endif