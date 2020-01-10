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

	void Init(void);
	void Update();
	void Draw();
	// チュートリアルの説明画面を表示
	void ShowTutorial(HelpTextureType Type);
	// ヘルプテキストを表示
	void SetHelpMessage(void);
	void SetIsShowTexture(bool Flag) { this->IsShowTexture = Flag; };
	bool GetIsShowTexture(void) { return this->IsShowTexture; };
	void SetActive(bool Flag) { this->isPlaying = Flag; };

private:
	TextureDrawer *BackGround;
	TextureDrawer *MessageFrame;
	std::vector<TextureDrawer*> HelpTexture;
	TextViewer *DescriptionText;
	TextViewer *ExitText;
	int TextureNum;
	bool IsShowTexture;
};

#endif