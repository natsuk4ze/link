#include "GuideViewer.h"

GuideViewer::GuideViewer()
{
	actor = new GuideActor();
}

GuideViewer::~GuideViewer()
{
	SAFE_DELETE(actor);
}

void GuideViewer::Update()
{
	actor->Update();
}

void GuideViewer::Draw()
{
	actor->Draw();
}

void GuideViewer::ChangeAnim(GuideActor::AnimState next)
{
	actor->ChangeAnim(next);
}