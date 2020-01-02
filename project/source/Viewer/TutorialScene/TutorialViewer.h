//=============================================================================
//
// チュートリアルビューアクラス [TutorialViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _TutorialViewer_H_
#define _TutorialViewer_H_

#include "../../../main.h"
#include "../Framework/BaseViewer.h"

#include <functional>
#include <vector>

/**************************************
前方宣言
***************************************/
class TextureDrawer;
class TextViewer;

/**************************************
クラス定義
***************************************/
class TutorialViewer : public BaseViewer
{
public:
	enum HelpTextureType
	{
		LinkRoad,
		Develop,
		ChangeCamera,
		EventHappend,
		HighScore,
		Max,
	};

	TutorialViewer();
	~TutorialViewer();

	void Update();
	void Draw();
	void ShowTutorial(HelpTextureType Type);

private:
	TextureDrawer *BackGround;
	TextureDrawer *MessageFrame;
	std::vector<TextureDrawer*> HelpTexture;
	TextViewer *DescriptionText;
	TextViewer *TitleText;
	int TextureNum;
};

#endif