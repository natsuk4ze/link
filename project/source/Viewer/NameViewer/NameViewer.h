//=====================================
//
// ネームビュアー[NameViewer.h]
// 機能：名前表示用
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _NAMEVIEWER_H_
#define _NAMEVIEWER_H_

#include "../../../main.h"
#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

//**************************************
// クラス定義
//**************************************
class NameViewer
{
public:
	NameViewer();
	~NameViewer();

	void Update();
	void Draw();

	// 初期座標、サイズの設定
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

	// 名前をセット（配列の先頭ポインタを入れる、Initを呼び出してから使用する）
	void SetName(int* Buff);

	void SetSize(const float& x, const float& y);
	void SetPosition(const D3DXVECTOR3& pos);

private:
	static const int NumChar = 3;	// 文字数
	static const int DivideX = 6;	// テクスチャ分割数
	static const int DivideY = 6;	// テクスチャ分割数
	inline static float Width = 1.0f / 6.0f;
	inline static float Height = 1.0f / 6.0f;

	Polygon2D* polygon[NumChar];
	D3DXVECTOR3 stdPosition;		// 基準になる座標（中心の文字の中心）
	float interval;					// 文字の間の距離
};


#endif