#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& pos, const int& level):
	InfoActor(pos, level)
{
	for (int i = 0; i < MaxDigit; i++)
	{
		digit[i] = new DigitActor();
	}
}

//=====================================
// デストラクタ
//=====================================
LinkInfoActor::~LinkInfoActor()
{
	for (int i = 0; i < MaxDigit; i++)
	{
		SAFE_DELETE(digit[i]);
	}
}

//=====================================
// 更新
//=====================================
void LinkInfoActor::Update()
{
	for (int i = 0; i < MaxDigit; i++)
	{
		digit[i]->Update();
	}
}

//=====================================
// 描画
//=====================================
void LinkInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	//if (!onCamera)
	//	return;

	polygon->Draw(transform->GetMatrix());
	for (int i = 0; i < MaxDigit; i++)
	{
		digit[i]->Draw();
	}
}

DigitActor::DigitActor(int num)
{
	this->num = num;

}