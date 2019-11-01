//=====================================
//
// インフォディジット[InfoDigit.cpp]
// 機能：情報表示用数字
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "InfoDigit.h"

//**************************************
// スタティックメンバ初期化
//**************************************
const int InfoDigit::divideX = 4;
const int InfoDigit::divideY = 3;
const float InfoDigit::width = 1.0f / divideX;
const float InfoDigit::height = 1.0f / divideY;

//=====================================
// コンストラクタ
//=====================================
InfoDigit::InfoDigit(const int& num, const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	this->num = num;
	this->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
	this->SetSize(80.0f, 80.0f);

	int x = this->num % divideX;
	int y = this->num / divideX;
	float left = (float)x * width;
	float top = (float)y * height;
	this->SetUV(left, top, width, height);
	this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=====================================
// デストラクタ
//=====================================
InfoDigit::~InfoDigit()
{
}

//=====================================
// 更新
//=====================================
void InfoDigit::Update()
{
}

//=====================================
// 表示する数字の変更
//=====================================
void InfoDigit::ChangeDigit(const int& num)
{
	this->num = num;
	int x = this->num % divideX;
	int y = this->num / divideX;
	float left = (float)x * width;
	float top = (float)y * height;
	this->SetUV(left, top, width, height);
}