#include "GuideViewerBG.h"
#include "../../../../Framework/Resource/ResourceManager.h"

GuideViewerBG::GuideViewerBG()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("GuideViewerBG", polygon);

	transform->Rotate(0.0f, 0.0f, 0.0f);
	transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	transform->SetScale(Vector3::One);
}

GuideViewerBG::~GuideViewerBG()
{
	SAFE_DELETE(polygon);
}

void GuideViewerBG::Update()
{

}

void GuideViewerBG::Draw()
{
	polygon->Draw(transform->GetMatrix());
}
