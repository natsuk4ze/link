#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& pos, const int& level):
	InfoActor(pos), linkLevel(level)
{
	// 3Dビューワーの作成
	viewer = new Viewer3D(30, 10, D3DXVECTOR2(9.0f, 3.0f));

	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;

}

//=====================================
// デストラクタ
//=====================================
LinkInfoActor::~LinkInfoActor()
{
}

//=====================================
// 更新
//=====================================
void LinkInfoActor::Update()
{
}

//=====================================
// 描画
//=====================================
void LinkInfoActor::Draw()
{
	if (!this->IsActive())
		return;
}

// レベル変更時使用
void LinkInfoActor::SetLevel(const int& nextLevel)
{
	linkLevel = nextLevel;
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
}
