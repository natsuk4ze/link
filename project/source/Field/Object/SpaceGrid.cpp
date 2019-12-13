//=====================================
//
//SpaceGrid.cpp
//機能:宇宙レベルのグリッド
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpaceGrid.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../Shader/SpaceGridEffect.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
staticメンバ
***************************************/
const int SpaceGrid::PeriodFade = 210;

/**************************************
コンストラクタ
***************************************/
SpaceGrid::SpaceGrid()
{
	effect = new SpaceGridEffect();
	polygon = new BoardPolygon(effect);
	ResourceManager::Instance()->GetPolygon("SpaceGrid", polygon);

	polygon->SetTexDiv({ 0.02f, 0.02f });

	const D3DXVECTOR3 position = D3DXVECTOR3(250.0f, 0.0f, -250.0f) - D3DXVECTOR3(5.0f, 0.0f, -5.0f);
	transform->SetPosition(position);
	transform->Rotate(90.0f, Vector3::Right);
}

/**************************************
デストラクタ
***************************************/
SpaceGrid::~SpaceGrid()
{
	SAFE_DELETE(polygon);

	//effectはBoardPolygon側が削除するので何もしない
}

/**************************************
更新処理
***************************************/
void SpaceGrid::Update()
{
	cntFrame = Math::WrapAround(0, PeriodFade, ++cntFrame);
	float t = Easing::EaseValue((float)cntFrame / PeriodFade, 0.0f, 1.0f, EaseType::Linear);
	effect->SetTime(t);
}

/**************************************
描画処理
***************************************/
void SpaceGrid::Draw()
{
	polygon->Draw(transform->GetMatrix());
}
