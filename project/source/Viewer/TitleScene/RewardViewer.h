//=============================================================================
//
// リワードビューアクラス [RewardViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _RewardViewer_H_
#define _RewardViewer_H_

#include "../../Viewer/Framework/BaseViewer.h"
#include <vector>
using std::vector;

class TextureDrawer;
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RewardViewer : public BaseViewer
{
private:
	vector<TextureDrawer*> TextureVec;
	TextureDrawer* Title;
	TextureDrawer* RewardIcon;
	TextureDrawer* RewardFrame;
	TextureDrawer* RewardName;
	TextureDrawer* Cursor;
	TextViewer* Text;

	void CursorMove(void);

public:
	RewardViewer();
	~RewardViewer();
	void Update(void);
	void Draw(void);
};

#endif
